#include "slime.h"
#include <algorithm>

Slime::Slime(const std::string &name, SlimeType type, int maxHP, int attack, int defense, int speed)
    : name(name), type(type), maxHP(maxHP), currentHP(maxHP), attack(attack), defense(defense), speed(speed)
{
    skills.emplace_back("Tackle", SkillType::Normal, 20, 100, 0);
    switch (type)
    {
    case SlimeType::Grass:
        skills.emplace_back("Leaf", SkillType::Grass, 20, 100, 0);
        break;
    case SlimeType::Fire:
        skills.emplace_back("Flame", SkillType::Fire, 20, 100, 0);
        break;
    case SlimeType::Water:
        skills.emplace_back("Stream", SkillType::Water, 20, 100, 0);
        break;
    }
}

std::string Slime::getName() const { return name; }
SlimeType Slime::getType() const { return type; }
int Slime::getCurrentHP() const { return currentHP; }
int Slime::getMaxHP() const { return maxHP; }
int Slime::getAttack() const { return attack; }
int Slime::getDefense() const { return defense; }
int Slime::getSpeed() const { return speed; }
const std::vector<Skill> &Slime::getSkills() const { return skills; }

void Slime::takeDamage(int damage)
{
    currentHP = std::max(0, currentHP - damage);
}

bool Slime::isDefeated() const
{
    return currentHP == 0; // == 0 also works bacause we apply std::max when taking damage to avoid negative HP
}

void Slime::heal(int amount)
{
    currentHP = std::min(maxHP, currentHP + amount);
}