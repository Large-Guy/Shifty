#include "TextEditSystems.h"

#include <chrono>
#include <complex>
#include <iostream>

#include "Components/Edit.h"
#include "Components/Focus.h"
#include "Components/Text.h"
#include "ECS/Entity.h"

void EditShared::handleTextInput(const OnTextInput& input)
{
    std::cout << "Input event" << std::endl;
    Entity::multiEach<Text, Edit>([input](Text& text, Edit& edit)
                                  {
                                      if (text.text.data() == nullptr)
                                      {
                                          std::cout << "Data is null!" << std::endl;
                                          return;
                                      }

                                      if (edit.highlighting)
                                      {
                                          deleteSelection(text, edit);
                                      }
                                      text.text.insert(edit.cursor, input.input);
                                      edit.cursor += input.input.length();
                                  }, [](Entity entity, Text& _text, Edit& _edit)
                                  {
                                      return Entity::find<Focus>().focused == entity;
                                  });
}

std::pair<size_t, size_t> EditShared::getSelection(Edit& edit)
{
    return {std::min(edit.highlightStart, edit.cursor), std::max(edit.highlightStart, edit.cursor)};
}

std::string EditShared::getSelectedText(Text& text, Edit& edit)
{
    auto [start, end] = getSelection(edit);
    return text.text.substr(start, end - start);
}

void EditShared::deleteSelection(Text& text, Edit& edit)
{
    auto [start, end] = getSelection(edit);
    text.text.erase(start, end - start);
    edit.cursor = start;
    clearSelection(edit);
}

void EditShared::clearSelection(Edit& edit)
{
    edit.highlighting = false;
}

void EditShared::select(Edit& edit)
{
    if (!edit.highlighting)
    {
        edit.highlightStart = edit.cursor;
        edit.highlighting = true;
    }
}


void EditInput::process(const OnTextInput& input)
{
    EditShared::handleTextInput(input);
}

void EditKeydown::process(const OnKeyPress& input)
{
    bool shift = input.handler.isPressed(SDLK_LSHIFT) || input.handler.isPressed(SDLK_RSHIFT);
    bool ctrl = input.handler.isPressed(SDLK_LCTRL) || input.handler.isPressed(SDLK_RCTRL);
    switch (input.key)
    {
    case SDLK_BACKSPACE:
        {
            Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                          {
                                              if (edit.highlighting)
                                              {
                                                  EditShared::deleteSelection(text, edit);
                                              }
                                              else if (edit.cursor > 0)
                                              {
                                                  if (ctrl)
                                                  {
                                                      //Delete word
                                                  }
                                                  else
                                                  {
                                                      text.text.erase(edit.cursor - 1, 1);
                                                      edit.cursor--;
                                                  }
                                              }
                                          }, [](Entity entity, Text& _text, Edit& _edit)
                                          {
                                              return Entity::find<Focus>().focused == entity;
                                          });
            break;
        }
    case SDLK_DELETE:
        {
            Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                          {
                                              if (edit.highlighting)
                                              {
                                                  EditShared::deleteSelection(text, edit);
                                              }
                                              else if (edit.cursor > 0)
                                              {
                                                  if (ctrl)
                                                  {
                                                      //Delete word
                                                  }
                                                  else
                                                  {
                                                      text.text.erase(edit.cursor - 1, 1);
                                                      edit.cursor--;
                                                  }
                                              }
                                          }, [](Entity entity, Text& _text, Edit& _edit)
                                          {
                                              return Entity::find<Focus>().focused == entity;
                                          });
            break;
        }
    case SDLK_LEFT:
        {
            Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                          {
                                              if (shift)
                                              {
                                                  EditShared::select(edit);
                                              }
                                              else
                                              {
                                                  EditShared::clearSelection(edit);
                                              }

                                              if (!edit.cursor > 0)
                                                  return;

                                              if (ctrl)
                                              {
                                                  //Move by word
                                              }
                                              else
                                              {
                                                  edit.cursor--;
                                              }
                                          }, [](Entity entity, Text& _text, Edit& _edit)
                                          {
                                              return Entity::find<Focus>().focused == entity;
                                          });
            break;
        }
    case SDLK_RIGHT:
        {
            Entity::multiEach<Text, Edit>([&](const Text& text, Edit& edit)
                                          {
                                              if (shift)
                                              {
                                                  EditShared::select(edit);
                                              }
                                              else
                                              {
                                                  EditShared::clearSelection(edit);
                                              }

                                              if (edit.cursor >= text.text.length())
                                                  return;

                                              if (ctrl)
                                              {
                                                  //Move by word
                                              }
                                              else
                                              {
                                                  edit.cursor++;
                                              }
                                          }, [](Entity entity, Text& _text, Edit& _edit)
                                          {
                                              return Entity::find<Focus>().focused == entity;
                                          });
            break;
        }
    case SDLK_A:
        {
            if (ctrl)
            {
                Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                              {
                                                  edit.highlightStart = 0;
                                                  edit.cursor = text.text.length();
                                                  edit.highlighting = edit.cursor > 0;
                                              }, [](Entity entity, Text& _text, Edit& _edit)
                                              {
                                                  return Entity::find<Focus>().focused == entity;
                                              });
            }
            break;
        }
    case SDLK_C:
        {
            if (ctrl)
            {
                Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                              {
                                                  if (!edit.highlighting)
                                                      return;

                                                  std::string highlighted = EditShared::getSelectedText(text, edit);
                                                  SDL_SetClipboardText(highlighted.c_str());
                                              }, [](Entity entity, Text& _text, Edit& _edit)
                                              {
                                                  return Entity::find<Focus>().focused == entity;
                                              });
            }
            break;
        }
    case SDLK_V:
        {
            if (ctrl)
            {
                Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                              {
                                                  char* clipboardText = SDL_GetClipboardText();
                                                  if (clipboardText != nullptr)
                                                  {
                                                      EditShared::handleTextInput(OnTextInput{
                                                          input.handler, std::string(clipboardText)
                                                      });
                                                      SDL_free(clipboardText);
                                                  }
                                              }, [](Entity entity, Text& _text, Edit& _edit)
                                              {
                                                  return Entity::find<Focus>().focused == entity;
                                              });
            }
            break;
        }
    case SDLK_X:
        {
            if (ctrl)
            {
                Entity::multiEach<Text, Edit>([&](Text& text, Edit& edit)
                                              {
                                                  if (!edit.highlighting)
                                                      return;

                                                  std::string highlighted = EditShared::getSelectedText(text, edit);
                                                  SDL_SetClipboardText(highlighted.c_str());
                                                  EditShared::deleteSelection(text, edit);
                                              }, [](Entity entity, Text& _text, Edit& _edit)
                                              {
                                                  return Entity::find<Focus>().focused == entity;
                                              });
            }
        }
    default:
        break;
    }
}

void EditProcess::process(const OnUpdate& onUpdate)
{
    Entity::find<InputHandler>().textInput = false; //TODO: Maybe find a better way to do this cuz it's a little sketch
    Entity::multiEach<Edit>([](Edit& edit)
    {
        Entity::find<InputHandler>().textInput = true;
    });
}

EditDraw::Command::Command(const SDL_FRect render, Text& text, Edit& edit) : Draw::Command(200), render(render),
                                                                             text(text), edit(edit)
{
}

void EditDraw::Command::execute(SDL_Renderer* renderer)
{
    TTF_Font* font = text.font->size(text.size);
    const std::string tillCursor = text.text.substr(0, edit.cursor);
    const std::string tillSelection = text.text.substr(0, edit.highlightStart);

    //Cursor
    float cursorX, h;
    TextRenderer::sizeText(font, tillCursor, &cursorX, &h);

    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    double time = std::chrono::duration<double>(duration).count();

    double blinkRate = 2.0f;
    double adjusted = (2 * M_PI) * blinkRate;

    double blink = std::clamp(std::sin(time * adjusted), 0.0, 1.0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, blink * 255.0);
    SDL_RenderLine(renderer, cursorX + render.x, render.y, cursorX + render.x, render.y + h);

    //Selection
    if (!edit.highlighting)
        return;

    float selectionX, h2;
    TextRenderer::sizeText(font, tillSelection, &selectionX, &h2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 96);
    float startX = std::min(cursorX, selectionX);
    float endX = std::max(cursorX, selectionX);
    SDL_FRect rect = {startX + render.x, render.y, endX - startX, h};
    SDL_RenderFillRect(renderer, &rect);
}


void EditDraw::process(const OnDraw& onDraw)
{
    Entity::multiEach<Text, Edit, RenderTransform>(
        [&](Text& text, Edit& edit, const RenderTransform& renderTransform)
        {
            float x = renderTransform.x;
            float y = renderTransform.y;

            float w, h;

            TextRenderer::sizeText(text.font->size(text.size), text.text, &w, &h);

            switch (text.horizontal)
            {
            case Text::Alignment::Leading:
                break;
            case Text::Alignment::Center:
                x += renderTransform.w / 2 - w / 2;
                break;
            case Text::Alignment::Trailing:
                x += renderTransform.w - w / 2;
                break;
            }

            switch (text.vertical)
            {
            case Text::Alignment::Leading:
                break;
            case Text::Alignment::Center:
                y += renderTransform.h / 2 - h / 2;
                break;
            case Text::Alignment::Trailing:
                y += renderTransform.h - h / 2;
                break;
            }

            h = std::min(renderTransform.h, h);

            onDraw.draw.pushCommand(std::make_shared<Command>(SDL_FRect{x, y, w, h}, text, edit));
        }, [](Entity entity, Text& text, Edit& edit, const RenderTransform& renderTransform)
        {
            return Entity::find<Focus>().focused == entity;
        });
}
