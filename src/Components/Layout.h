#ifndef SHIFTY_LAYOUT_H
#define SHIFTY_LAYOUT_H

/**
 * @class Layout
 * @brief Handles layouts of open views/panels.
 */
struct Layout {
    enum class Type {
        FULL,
        VERTICAL,
        HORIZONTAL
    };

    Type type = Type::FULL;
};

#endif //SHIFTY_LAYOUT_H
