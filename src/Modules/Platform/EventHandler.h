#ifndef SHIFTY_INPUTHANDLER_H
#define SHIFTY_INPUTHANDLER_H

#include <unordered_map>
#include <memory>
#include <string>

#include "EventBus/EventBus.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_video.h"

class EventHandler : public std::enable_shared_from_this<EventHandler>
{
public:
    bool textInput = false;
    std::unordered_map<SDL_Keycode, bool> keyStates = {};

    bool isPressed(SDL_Keycode keycode);
    void pollEvents();
};

struct OnWindowResize 
{
    SDL_Window* window;
    int width, height;
};

struct OnWindowMove 
{
    SDL_Window* window;
    int x, y;
};

struct OnWindowClose 
{
    SDL_Window* window;
};

struct OnKeyPress 
{
    std::shared_ptr<EventHandler> handler;
    SDL_Keycode key;
};

struct OnKeyRelease 
{
    std::shared_ptr<EventHandler> handler;
    SDL_Keycode key;
};

struct OnTextInput 
{
    std::shared_ptr<EventHandler> handler;
    const std::string& input;
};

struct OnMouseButtonPress 
{
    std::shared_ptr<EventHandler> handler;
    float x, y;
    int button;
};

struct OnMouseButtonRelease 
{
    std::shared_ptr<EventHandler> handler;
    float x, y;
    int button;
};

#endif //SHIFTY_INPUTHANDLER_H
