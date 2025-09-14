#include "Layout.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

size_t Panel::nextId = 0;
std::unordered_map<size_t, Panel *> Panel::idMap = {};

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
            children[0]->x = this->x;
            children[0]->y = this->y;
            children[0]->w = this->w;
            children[0]->h = this->h;
        }
    } else if (type == Type::VERTICAL) {
        for (int i = 0; i < children.size(); ++i) {
            const auto &child = children[i];
            child->x = this->x;
            child->y = this->y + static_cast<float>(i) * (this->h / static_cast<float>(children.size()));
            child->w = this->w;
            child->h = this->h / static_cast<float>(children.size());
        }
    } else if (type == Type::HORIZONTAL) {
        for (int i = 0; i < children.size(); ++i) {
            const auto &child = children[i];
            child->x = this->x + static_cast<float>(i) * (this->w / static_cast<float>(children.size()));
            child->y = this->y;
            child->w = this->w / static_cast<float>(children.size());
            child->h = this->h;
        }
    }

    for (auto &child: children) {
        child->computeLayout();
    }
}

