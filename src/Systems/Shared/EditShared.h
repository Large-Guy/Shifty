#ifndef SHIFTY_EDITSHARED_H
#define SHIFTY_EDITSHARED_H
#include "Components/Edit.h"
#include "Components/InputHandler.h"
#include "Components/Text.h"

class EditShared
{
public:
    static void handleTextInput(const OnTextInput& input);
    static std::pair<size_t, size_t> getSelection(ComRef<Edit> edit);
    static std::string getSelectedText(ComRef<Text> text, ComRef<Edit> edit);
    static void deleteSelection(ComRef<Text> text, ComRef<Edit> edit);
    static void clearSelection(ComRef<Edit> edit);
    static void select(ComRef<Edit> edit);
};


#endif //SHIFTY_EDITSHARED_H
