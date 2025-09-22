#include "CommandPalette.h"

using namespace Shifty;

void CommandPalette::open() {
    isOpen = true;
}

void CommandPalette::close() {
    isOpen = false;
}

void CommandPalette::update() {
    openTime += 0.016f;
}

void CommandPalette::render() {

}