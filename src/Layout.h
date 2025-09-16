#ifndef SHIFTY_LAYOUT_H
#define SHIFTY_LAYOUT_H

#include <memory>
#include <unordered_map>
#include <vector>

/**
 * @class Layout
 * @brief Handles layouts of open views/panels.
 */
class Layout {
private:
    static size_t nextId;
    static std::unordered_map<size_t, Layout *> idMap;

public:
    enum class Type {
        FULL,
        VERTICAL,
        HORIZONTAL
    };

    enum class Mode {
        DISABLE,
        PERCENT,
    };

    bool operator==(const Layout &other) const {
        return this->id == other.id;
    }

    size_t id = 0;

    Type type = Type::FULL;

    Mode widthMode = Mode::DISABLE;
    float width = 0;
    Mode heightMode = Mode::DISABLE;
    float height = 0;

    float renderX = 0.f, renderY = 0.f, renderWidth = 1.f, renderHeight = 1.f;

    Layout *parent = nullptr;
    std::vector<std::shared_ptr<Layout> > children = {};

    explicit Layout(Type type);

    void addChild(const std::shared_ptr<Layout> &panel);

    void removeChild(const std::shared_ptr<Layout> &panel);

    void computeLayout() const;
};

#endif //SHIFTY_LAYOUT_H
