#include "TextRenderer.h"

#include <ostream>

TTF_TextEngine* TextRenderer::engine = nullptr;

TTF_GPUAtlasDrawSequence* TextRenderer::getTexture(std::shared_ptr<Device> device, TTF_Font* font,
                                                   const std::string& text)
{
    if (!engine)
        engine = TTF_CreateGPUTextEngine(device->getDevice());

    TTF_Text* drawtext = TTF_CreateText(engine, font, text.c_str(), text.size());
    TTF_GPUAtlasDrawSequence* atlas = TTF_GetGPUTextDrawData(drawtext);
    TTF_DestroyText(drawtext);
    return atlas;
}

void TextRenderer::sizeText(TTF_Font* font, const std::string& text, float* w, float* h)
{
    int width, height;
    TTF_GetStringSize(font, text.c_str(), text.length(), &width, &height);
    *w = static_cast<float>(width);
    *h = static_cast<float>(height);
}

