#include "Layout.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

/* This is complicated so I'm saving it for later
void Layout::computeLayout() const {
    if (type == Type::FULL) {
        if (children.size() > 1) {
            throw std::runtime_error("Full layout can only have one child");
        }
        if (!children.empty()) {
            children[0]->renderX = this->renderX;
            children[0]->renderY = this->renderY;
            children[0]->renderWidth = this->renderWidth;
            children[0]->renderHeight = this->renderHeight;
        }
    } else if (type == Type::VERTICAL) {
        float offset = 0.f;
        float remainder = this->renderHeight;
        int autoCount = 0;
        for (const auto &child: children) {
            switch (child->heightMode) {
                case Mode::PERCENT: {
                    remainder -= child->height * this->renderHeight;
                    break;
                }
                case Mode::DISABLE:
                    autoCount++;
                    break;
            }
        }
        for (int i = 0; i < children.size(); ++i) {
            const auto &child = children[i];
            child->renderX = this->renderX;
            child->renderY = this->renderY + offset;
            child->renderWidth = this->renderWidth;
            switch (child->heightMode) {
                case Mode::PERCENT: {
                    child->renderHeight = this->renderHeight * child->height;
                    break;
                }
                case Mode::DISABLE: {
                    child->renderHeight = remainder / static_cast<float>(autoCount);
                    break;
                }
            }
            offset += child->renderHeight;
        }
    } else if (type == Type::HORIZONTAL) {
        float offset = 0.f;
        float remainder = this->renderWidth;
        int autoCount = 0;
        for (const auto &child: children) {
            switch (child->widthMode) {
                case Mode::PERCENT: {
                    remainder -= child->width * this->renderWidth;
                    break;
                }
                case Mode::DISABLE:
                    autoCount++;
                    break;
            }
        }
        for (int i = 0; i < children.size(); ++i) {
            const auto &child = children[i];
            child->renderX = this->renderX + offset;
            child->renderY = this->renderY;
            child->renderHeight = this->renderHeight;
            switch (child->widthMode) {
                case Mode::PERCENT: {
                    child->renderWidth = this->renderWidth * child->width;
                    break;
                }
                case Mode::DISABLE: {
                    child->renderWidth = remainder / static_cast<float>(autoCount);
                    break; //Ignore
                }
            }
            offset += child->renderWidth;
        }
    }

    for (auto &child: children) {
        child->computeLayout();
    }
}
*/

void Layout::addChild(const Entity to, const Entity add)
{
    if (!to.has<Layout>())
        throw std::runtime_error("Parent entity is missing layout component");
    if (!add.has<Layout>())
        throw std::runtime_error("Child entity is missing layout component!");
    Layout& layout = to.get<Layout>();
    Layout& other = add.get<Layout>();
    if (other.parent != nullptr)
    {
        removeChild(other.parent, add);
    }
    other.parent = to;
    layout.children.push_back(add);
}

void Layout::removeChild(const Entity from, const Entity remove)
{
    if (!from.has<Layout>())
        throw std::runtime_error("Parent entity is missing layout component");
    if (remove.has<Layout>())
        throw std::runtime_error("Child entity is missing layout component!");
}
