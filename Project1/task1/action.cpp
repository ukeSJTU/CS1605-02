#include "action.h"

Action::Action(ActionType type, int index, int priority) : type(type), index(index), priority(priority) {}

ActionType Action::getType() const { return type; }
int Action::getIndex() const { return index; }
int Action::getPriority() const { return priority; }