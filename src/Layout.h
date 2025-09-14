#ifndef SHIFTY_LAYOUT_H
#define SHIFTY_LAYOUT_H
#include <memory>
#include <vector>

class Panel {
public:
    enum class Type {
        FULL,
        VERTICAL,
        HORIZONTAL
    };

    bool operator==(const Panel &other) const {
        return this->id == other.id;
    }

    size_t id = 0;

    Type type = Type::FULL;

    float x = 0.f, y = 0.f, w = 1.f, h = 1.f;

    Panel *parent = nullptr;
    std::vector<std::unique_ptr<Panel> > children = {};

    explicit Panel(Type type);

    void addChild(std::unique_ptr<Panel> panel);

    void removeChild(std::unique_ptr<Panel> panel);

    void computeLayout() const;
};

#endif //SHIFTY_LAYOUT_H
