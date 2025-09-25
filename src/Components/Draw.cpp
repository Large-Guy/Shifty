#include "Draw.h"

Draw::Command::Command(int priority) {
    this->priority = priority;
}


void Draw::pushCommand(const std::shared_ptr<Command> &command) {
    auto iter = commands.begin();
    for (; iter != commands.end(); ++iter) {
        if (command->priority < (*iter)->priority) {
            break;
        }
    }
    commands.insert(iter, command);
}
