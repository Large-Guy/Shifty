#ifndef SHIFTY_TEXTEDIT_H
#define SHIFTY_TEXTEDIT_H
#include <cstdint>
#include <string>


struct TextEdit
{
    std::string text;

    int cursor;
    int cursorLength;
    bool cursorVisible;
    uint64_t lastCursorChange;

    bool highlighting;
    int highlightStart;
    int highlightEnd;

    int compositionStart;
    int compositionLength;
    int compositionCursor;
    int compositionCursorLength;
};


#endif //SHIFTY_TEXTEDIT_H
