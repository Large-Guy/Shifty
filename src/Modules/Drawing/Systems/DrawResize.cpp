#include "DrawResize.h"

#include "Drawing/Components/Draw.h"
#include "ECS/Entity.h"

void DrawResize::process(const OnWindowResize& resize)
{
    Entity::each<Draw>([resize](ComRef<Draw> draw)
                       {
                           draw->width = resize.width;
                           draw->height = resize.height;

                           draw->renderTexture = std::make_shared<Texture>(
                               draw->device, resize.width, resize.height, TextureFormat::R8G8B8A8_SRGB, true);

                           draw->transferBuffer = std::make_shared<TransferBuffer>(
                               draw->device, resize.width * resize.height * 4);

                           draw->outputTexture = SDL_CreateTexture(draw->renderer, SDL_PIXELFORMAT_RGBA32,
                                                                   SDL_TEXTUREACCESS_STREAMING, resize.width,
                                                                   resize.height);
                           draw->drawPass = std::make_shared<RenderPass>(draw->device, draw->renderTexture);
                       },
                       [resize](ComRef<Draw> draw)
                       {
                           return SDL_GetRenderWindow(draw->renderer) == resize.window;
                       });
}
