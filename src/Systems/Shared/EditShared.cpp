#include "EditShared.h"

#include "Components/Focus.h"

void EditShared::handleTextInput(const OnTextInput& input)
{
    Entity::multiEach<Text, Edit>([input](ComRef<Text> text, ComRef<Edit> edit)
                                  {
                                      if (text->text.data() == nullptr)
                                      {
                                          throw std::runtime_error("Text is null");
                                          return;
                                      }

                                      if (edit->highlighting)
                                      {
                                          deleteSelection(text, edit);
                                      }
                                      text->text.insert(edit->cursor, input.input);
                                      edit->cursor += input.input.length();
                                  }, [](Entity entity, ComRef<Text>, ComRef<Edit>)
                                  {
                                      return Entity::find<Focus>()->focused == entity;
                                  });
}

std::pair<size_t, size_t> EditShared::getSelection(ComRef<Edit> edit)
{
    return {std::min(edit->highlightStart, edit->cursor), std::max(edit->highlightStart, edit->cursor)};
}

std::string EditShared::getSelectedText(ComRef<Text> text, ComRef<Edit> edit)
{
    auto [start, end] = getSelection(edit);
    return text->text.substr(start, end - start);
}

void EditShared::deleteSelection(ComRef<Text> text, ComRef<Edit> edit)
{
    auto [start, end] = getSelection(edit);
    text->text.erase(start, end - start);
    edit->cursor = start;
    clearSelection(edit);
}

void EditShared::clearSelection(ComRef<Edit> edit)
{
    edit->highlighting = false;
}

void EditShared::select(ComRef<Edit> edit)
{
    if (!edit->highlighting)
    {
        edit->highlightStart = edit->cursor;
        edit->highlighting = true;
    }
}
