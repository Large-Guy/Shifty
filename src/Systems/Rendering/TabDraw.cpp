#include "TabDraw.h"

#include <iostream>
#include <random>

#include "Drawing.h"
#include "Tween.h"
#include "Components/Animation.h"
#include "Components/Focus.h"
#include "Components/RenderTransform.h"
#include "Components/Transform.h"
#include "Components/Panel.h"
#include "ECS/Entity.h"

//Temporary coloring functions
static void RGBtoHSL(float r, float g, float b, float* h, float* s, float* l)
{
    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    *l = (max + min) * 0.5f;

    if (max == min)
    {
        *h = *s = 0.0f; // Gray
        return;
    }

    float d = max - min;
    *s = (*l > 0.5f) ? d / (2.0f - max - min) : d / (max + min);

    if (max == r)
        *h = fmodf(((g - b) / d + (g < b ? 6.0f : 0.0f)), 6.0f);
    else if (max == g)
        *h = ((b - r) / d) + 2.0f;
    else
        *h = ((r - g) / d) + 4.0f;

    *h /= 6.0f;
}

// Helper: HSL → RGB
static float hueToRGB(float p, float q, float t)
{
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}

static void HSLtoRGB(float h, float s, float l, float* r, float* g, float* b)
{
    if (s == 0.0f)
    {
        *r = *g = *b = l;
        return;
    }

    float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
    float p = 2.0f * l - q;

    *r = hueToRGB(p, q, h + 1.0f / 3.0f);
    *g = hueToRGB(p, q, h);
    *b = hueToRGB(p, q, h - 1.0f / 3.0f);
}

// Main function
SDL_FColor makeShadowColor(SDL_FColor base)
{
    float h, s, l;
    RGBtoHSL(base.r, base.g, base.b, &h, &s, &l);

    // Adjust for more natural shadow
    h = fmodf(h + 0.05f, 1.0f); // small hue shift toward cooler tones (≈ +18°)
    s *= 0.9f; // slightly less saturated
    l *= 0.9f; // darker

    SDL_FColor shadow;
    HSLtoRGB(h, s, l, &shadow.r, &shadow.g, &shadow.b);
    shadow.a = base.a; // preserve alpha
    return shadow;
}

TabDraw::Command::Command(ComRef<RenderTransform> renderTransform, ComRef<Motion> motion, ComRef<Tab> tab, int layer) :
    Draw::Command(30 - layer),
    tab(tab),
    renderTransform(renderTransform), motion(motion)
{
}

void TabDraw::Command::execute(SDL_Renderer* renderer)
{
    float x = renderTransform->x;
    float y = renderTransform->y;
    float w = renderTransform->w;
    float h = renderTransform->h;

    float deltaX = motion->deltaX;
    float deltaY = motion->deltaY;
    float deltaW = motion->deltaW;
    float deltaH = motion->deltaH;

    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    std::mt19937 gen((size_t)renderTransform.get());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float r = dist(gen);
    float g = dist(gen);
    float b = dist(gen);

    float length = sqrt(r * r + g * g + b * b);

    r /= length;
    g /= length;
    b /= length;

    SDL_FColor color = {r, g, b, 1.0f};
    SDL_FColor shadow = makeShadowColor(color);

    float tween = 0.0f;

    if (Entity::find<Focus>()->focused.has<Panel>())
    {
        if (Entity::find<Focus>()->focused.get<Panel>()->holdingTabs.front() == tab.owner)
            tween = Tween::easeOutQuint(Entity::findEntity<Focus>().get<Animation>()->tracks["focus"].time);
    }

    ComRef<Draw> draw = Entity::find<Draw>();
    Drawing::drawUIRect(draw, {
                            .screenSize = {static_cast<float>(draw->width), static_cast<float>(draw->height)},
                            .start = {0.0f, 0.0f},
                            .rect = {rect.x, rect.y, rect.w, rect.h},
                            .rounding = {16.0f, 16.0f, 16.0f, 16.0f},

                            .fillStart = {color.r, color.g, color.b, 1.0f},
                            .fillEnd = {shadow.r, shadow.g, shadow.b, 1.0f},
                            .end = {0.0f, 1.0f},

                            .thickness = 1.0f,
                            .motion = {deltaX, deltaY, deltaW, deltaH},
                            .shadow = 32.0f,
                            .startShadow = Tween::Lerp(0.2f, 0.9f, tween),
                            .endShadow = 0.0
                        });
}

void TabDraw::process(const OnDraw& draw)
{
    Entity::multiEach<RenderTransform, Panel>(
        [draw](ComRef<RenderTransform> transform, ComRef<Panel> view)
        {
            if (view->holdingTabs.empty())
                return;

            for (int i = 0; i < view->holdingTabs.size(); ++i)
            {
                draw.draw->pushCommand(
                    std::make_shared<Command>(view->holdingTabs[i].get<RenderTransform>(),
                                              view->holdingTabs[i].get<Motion>(),
                                              view->holdingTabs[i].get<Tab>(), i));
            }
        });
}
