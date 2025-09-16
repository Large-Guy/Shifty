#include "ShiftyApp.h"

#include <cmath>
#include <iostream>
#include <ostream>
#include <random>

ShiftyApp::ShiftyApp() {
}

ShiftyApp::~ShiftyApp() {
}

void ShiftyApp::run() {
    int w = 1080, h = 720;
    window = SDL_CreateWindow("Shifty", 1080, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    //Calculate DPI scale factor
    int rw, rh;
    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_GetRenderOutputSize(renderer, &rw, &rh);
    float sw = (float) rw / (float) w;
    float sh = (float) rh / (float) h;
    SDL_SetRenderScale(renderer, sw, sh);

    SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

    text = {renderer};

    workspaceRoot.push_back(std::make_unique<Panel>(Panel::Type::FULL));
    auto &root = workspaceRoot[0];

    auto horizontalLayout = std::make_unique<Panel>(Panel::Type::HORIZONTAL);

    auto hone = std::make_unique<Panel>(Panel::Type::VERTICAL);
    auto htwo = std::make_unique<Panel>(Panel::Type::VERTICAL);
    auto hthree = std::make_unique<Panel>(Panel::Type::VERTICAL);

    auto vone = std::make_unique<Panel>(Panel::Type::FULL);
    auto vtwo = std::make_unique<Panel>(Panel::Type::FULL);
    auto vthree = std::make_unique<Panel>(Panel::Type::FULL);
    auto vfour = std::make_unique<Panel>(Panel::Type::FULL);
    auto vfive = std::make_unique<Panel>(Panel::Type::FULL);
    auto vsix = std::make_unique<Panel>(Panel::Type::FULL);

    hone->addChild(std::move(vone));
    hone->addChild(std::move(vtwo));

    htwo->addChild(std::move(vthree));
    htwo->addChild(std::move(vfour));

    hthree->addChild(std::move(vfive));
    hthree->addChild(std::move(vsix));

    horizontalLayout->addChild(std::move(hone));
    horizontalLayout->addChild(std::move(htwo));
    horizontalLayout->addChild(std::move(hthree));

    root->addChild(std::move(horizontalLayout));

    root->computeLayout();

    running = true;

    while (running) {
        update();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void ShiftyApp::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }
}

void ShiftyApp::drawPanel(SDL_FRect screen, const std::unique_ptr<Panel> &panel, int depth) {
    std::mt19937 rng(panel->id + depth * 10);
    std::uniform_real_distribution<double> dist(0., M_PI * 2.);
    const SDL_FRect rect = {
        panel->renderX * screen.w, panel->renderY * screen.h, panel->renderWidth * screen.w,
        panel->renderHeight * screen.h
    };

    const auto angle = dist(rng);
    auto h = std::fmod(angle, M_PI * 2.);
    auto s = 1.;
    auto v = 1.;

    auto c = v * s;
    auto x = c * (1. - std::abs(std::fmod(h, M_PI) - M_PI / 2.));
    auto m = v - c;

    double r = 0., g = 0., b = 0.;

    double degtorad = M_PI / 180.;

    if (angle < 60 * degtorad) {
        r = c;
        g = x;
        b = 0;
    } else if (angle < 120 * degtorad) {
        r = x;
        g = c;
        b = 0;
    } else if (angle < 180 * degtorad) {
        r = 0;
        g = c;
        b = x;
    } else if (angle < 240 * degtorad) {
        r = 0;
        g = x;
        b = c;
    } else if (angle < 300 * degtorad) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255),
                           static_cast<Uint8>(b * 255), 255);
    SDL_RenderRect(renderer, &rect);

    text.renderText("res/fonts/hack-regular.ttf", 16, std::to_string(panel->id), rect.x + depth * 16, rect.y);

    for (auto &child: panel->children) {
        drawPanel(screen, child, depth + 1);
    }
}

void ShiftyApp::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect iscreen = {};
    SDL_GetRenderViewport(renderer, &iscreen);

    SDL_FRect fscreen = {0, 0, (float) iscreen.w, (float) iscreen.h};
    drawPanel(fscreen, workspaceRoot[currentWorkspace]);

    SDL_RenderPresent(renderer);
}
