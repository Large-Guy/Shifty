#ifndef SHIFTY_DRAW_H
#define SHIFTY_DRAW_H

#include <memory>
#include <queue>
#include <vector>
#include <SDL3/SDL.h>

struct Draw
{
    struct Command
    {
        int priority = 0;

        virtual void execute(SDL_Renderer* renderer) = 0;

        Command(int priority)
        {
            this->priority = priority;
        }

        virtual ~Command() = default;
    };

    std::vector<std::shared_ptr<Command>> commands;
    SDL_Renderer* renderer;

    void pushCommand(const std::shared_ptr<Command>& command)
    {
        auto iter = commands.begin();
        for (; iter != commands.end(); ++iter)
        {
            if (command->priority < (*iter)->priority)
            {
                break;
            }
        }
        commands.insert(iter, command);
    }
};

struct OnDraw
{
    Draw& draw;
};

#endif //SHIFTY_DRAW_H
