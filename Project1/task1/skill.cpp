#include "skill.h"

Skill::Skill(const std::string &name, SkillType type, int power, int accuracy, int priority)
    : name(name), type(type), power(power), accuracy(accuracy), priority(priority) {}

std::string Skill::getName() const { return name; }
SkillType Skill::getType() const { return type; }
int Skill::getPower() const { return power; }
int Skill::getAccuracy() const { return accuracy; }
int Skill::getPriority() const { return priority; }