
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

cbuffer vert : register(b0, space1)
{
    // Positioning
    float2 v_screenSize;
    float2 v_start;

    float4 v_rect;
    float4 v_rounding;

    // Colors
    float4 v_fillStart;
    float4 v_fillEnd;

    float2 v_end;

    // Outline
    float v_thickness;
    float v_pad0;
}

cbuffer frag : register(b0, space3)
{
    // Positioning
    float2 f_screenSize;
    float2 f_start;

    float4 f_rect;
    float4 f_rounding;

    // Colors
    float4 f_fillStart;
    float4 f_fillEnd;

    float2 f_end;

    // Outline
    float f_thickness;
    float f_pad0;
}

//vertex

Output vertex(Input input)
{
    //Corners
    float2 tl = float2(0.0f, 0.0f);
    float2 tr = float2(1.0f, 0.0f);
    float2 bl = float2(0.0f, 1.0f);
    float2 br = float2(1.0f, 1.0f);

    Output output;
    float2 pos;
    if (input.VertexIndex == 0)
    {
        pos = tl;
        output.UV = tl;
    }
    if (input.VertexIndex == 1)
    {
        pos = tr;
        output.UV = tr;
    }
    if (input.VertexIndex == 2)
    {
        pos = bl;
        output.UV = bl;
    }
    if(input.VertexIndex == 3)
    {
        pos = bl;
        output.UV = bl;
    }
    if(input.VertexIndex == 4)
    {
        pos = tr;
        output.UV = tr;
    }
    if(input.VertexIndex == 5)
    {
        pos = br;
        output.UV = br;
    }

    float2 ss = max(v_screenSize, float2(1.0f, 1.0f)); // avoid div by 0

    pos *= v_rect.zw;
    pos /= (ss * 0.5f);
    pos -= float2(1.0f, 1.0f);
    pos += v_rect.xy / (ss * 0.5);
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
    const float4 outlineStart = float4(0.4, 0.4f, 0.4f, 1.0f);
    const float4 outlineEnd = float4(0.2f, 0.2f, 0.2f, 1.0f);
    const float4 background = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //gradient
    float2 ab = f_end - f_start;
    float2 ap = output.UV - f_start;
    float t = dot(ap, ab) / dot(ab, ab);
    float4 fill = lerp(f_fillStart, f_fillEnd, saturate(t));
    float4 outline = lerp(outlineStart, outlineEnd, saturate(t));

    float noise = (rand(output.UV * f_screenSize) - 0.5f) / 255.0f;

    fill += noise;

    float4 color = background;

    float2 pixelUV = (output.UV * f_rect.zw) - (f_rect.zw * 0.5f);

    float sdf = sdfRoundedBox(pixelUV * 2.0f, f_rect.zw, f_rounding);

    float smoothness = 0.9f;

    if(sdf < -f_thickness)
    {
        color = fill;
    }
    else if(sdf < 0.0f)
    {
        float t = smoothstep(0.0, -f_thickness, sdf);
        color = lerp(outline, fill, t);
    }
    else
    {
        color = background;
    }

    return color;
}
