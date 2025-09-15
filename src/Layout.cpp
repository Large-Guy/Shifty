#include "Layout.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

size_t Panel::nextId = 0;
std::unordered_map<size_t, Panel*> Panel::idMap = {};

Panel::Panel(const Type type) {
    this->type = type;
    this->id = nextId++;
}

void Panel::addChild(std::unique_ptr<Panel> panel) {
    if (panel->parent) {
        panel->parent->removeChild(std::move(panel));
    }

    panel->parent = this;
    children.push_back(std::move(panel));
}

void Panel::removeChild(std::unique_ptr<Panel> panel) {
    std::erase(children, panel);
}

void Panel::computeLayout() const {
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
        for (const auto& child: children) {
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
            const auto& child = children[i];
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
        for (const auto& child: children) {
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
            const auto& child = children[i];
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

    for (auto& child: children) {
        child->computeLayout();
    }
}

