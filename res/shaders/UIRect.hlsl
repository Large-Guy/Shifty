
struct Input
{
    uint VertexIndex : SV_VertexID;
};

struct Output
{
    float2 UV : TEXCOORD0;
    float4 Position : SV_Position;
};

//const float2 screenSize = float2(1080, 720);
//const float4 rect = float4(128, 128, 512, 512);
//const float4 rounding = float4(16.0f, 16.0f, 16.0f, 16.0f);
//const float4 fillStart = float4(0.1f, 0.1f, 0.1f, 1.0f);
//const float4 fillEnd = float4(0.05, 0.05, 0.05, 1.0f);
//const float2 start = float2(0.0f, 0.0f);
//const float2 end = float2(1.0f, 1.0f);
//const float thickness = 4.0;

struct RectInfo
{
    // Positioning
    float2 screenSize;
    float2 start;

    float4 rect;
    float4 rounding;

    // Color
    float4 fillStart;
    float4 fillEnd;

    float2 end;

    // Outline
    float thickness;
    float pad0;

    //Motion
    float4 motion;

    //  Effects

    //Border/shadow

    float shadow;
    float startShadow;
    float endShadow;
};

cbuffer vert : register(b0, space1)
{
    RectInfo vertInfo;
}


cbuffer frag : register(b0, space3)
{
    RectInfo fragInfo;
}


//vertex

const float2 tl = float2(0.0f, 0.0f);
const float2 tr = float2(1.0f, 0.0f);
const float2 bl = float2(0.0f, 1.0f);
const float2 br = float2(1.0f, 1.0f);

const float2 vertices[6] = {
    tl, tr, bl,
    bl, tr, br,
};

Output vertex(Input input)
{
    RectInfo info = vertInfo;

    //Corners
    Output output;
    float2 pos;

    pos = vertices[input.VertexIndex];
    output.UV = vertices[input.VertexIndex];

    float2 ss = max(info.screenSize, float2(1.0f, 1.0f)); // avoid div by 0

    float shadow = info.shadow;

    if(shadow > 0)
    {
        output.UV.y *= (info.rect.w + shadow) / info.rect.w;
    }

    pos *= (info.rect.zw + float2(0.0f, shadow));
    pos /= (ss * 0.5f);
    pos -= float2(1.0f, 1.0f);
    pos += (info.rect.xy) / (ss * 0.5);
    pos.y *= -1.0f;

    output.Position = float4(pos, 0.0f, 1.0f);
    return output;
}

//fragment

float rand(float2 n)
{
    return frac(sin(dot(n, float2(12.9898, 78.233))) * 43758.5453);
}

float sdfRoundedBox(in float2 p, in float2 b, in float4 r)
{
    r.xy = (p.x > 0.0f) ? r.xy : r.zw;
    r.x = (p.y > 0.0f) ? r.x : r.y;
    float2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0f) + length(max(q, 0.0f)) - r.x;
}

float4 fragment(Output output) : SV_TARGET
{
    RectInfo info = fragInfo;

    float shadow = info.shadow;

    const float4 outlineStart = float4(1.0, 1.0f, 1.0f, 1.0f);
    const float4 outlineEnd = float4(0.9f, 0.9f, 0.9f, 1.0f);
    const float4 background = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //gradient
    float2 ab = info.end - info.start;
    float2 ap = output.UV - info.start;
    float t = dot(ap, ab) / dot(ab, ab);
    float4 fill = lerp(info.fillStart, info.fillEnd, saturate(t));
    float4 outline = lerp(outlineStart, outlineEnd, saturate(t));

    float noise = (rand(output.UV * info.screenSize - float2(0.0f, shadow)) - 0.5f) / 255.0f;

    fill += noise;

    float4 color = background;

    float2 pixelUV = (output.UV * info.rect.zw);

    float sdf = sdfRoundedBox((pixelUV - info.rect.zw * 0.5f) * 2.0f, info.rect.zw, info.rounding);

    float smoothness = 0.0f;

    if(sdf < -info.thickness * 2.0)
    {
        color = fill;
    }
    else if(sdf < 0.0f)
    {
        float edge = 0.5;
        float aa = fwidth(sdf) * info.thickness * 2.0;  // approximate pixel width in distance space
        float alpha = smoothstep(edge - aa, edge + aa, sdf);
        color = lerp(outline, fill, alpha);
    }
    else
    {
        color = background;
        if(pixelUV.y > info.rect.w - max(info.rounding.x, info.rounding.z))
        {
            float shadowPos = 1.0f - clamp((pixelUV.y - info.rect.w) / shadow, 0.0f, 1.0f);
            float edgeFade = 1.0f - clamp((abs(pixelUV.x - info.rect.z / 2.0f) - (info.rect.z / 2.0f - shadow)) / shadow, 0.0f, 1.0f);
            color = float4(0.0f, 0.0f, 0.0f, lerp(info.endShadow, info.startShadow, edgeFade * shadowPos));
        }
    }


    return color;
}
