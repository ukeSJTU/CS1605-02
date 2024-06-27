#include "player.h"
#include "engine.h"
#include <iostream>

Player::Player(Strategy *strategy) : strategy(strategy), activeSlime(nullptr) {}

Player::~Player()
{
    for (auto slime : slimes)
    {
        delete slime;
    }
    delete strategy;
}

void Player::addSlime(Slime *slime)
{
    slimes.push_back(slime);
}

void Player::setActiveSlime(Slime *slime)
{
    activeSlime = slime;
}

Action Player::chooseAction(const Engine &engine)
{
    return strategy->chooseAction(engine);
}

Slime *Player::chooseStartingSlime(const Engine &engine)
{
    return strategy->chooseStartingSlime(slimes, engine);
}

Slime *Player::chooseNextSlime(const Engine &engine)
{
    return strategy->chooseNextSlime(slimes, engine);
}

Slime *Player::getActiveSlime() const
{
    return activeSlime;
}

const std::vector<Slime *> &Player::getSlimes() const
{
    return slimes;
}

bool Player::isDefeated() const
{
    for (const auto &slime : slimes)
    {
        if (!slime->isDefeated())
        {
            return false;
        }
    }
    return true;
}

void Player::addPotion(const Potion &potion)
{
    potions.push_back(potion);
}

const std::vector<Potion> &Player::getPotions() const
{
    return potions;
}

bool Player::usePotion(Potion::Type type, Slime *target)
{
    auto it = std::find_if(potions.begin(), potions.end(),
                           [type](const Potion &p)
                           { return p.getType() == type && !p.isUsed(); });
    if (it != potions.end())
    {
        it->use();
        if (type == Potion::Type::Attack && target)
        {
            target->boostAttack();
        }
        else if (type == Potion::Type::Revival)
        {
            // Find the first defeated slime and revive it
            auto defeatedSlime = std::find_if(slimes.begin(), slimes.end(),
                                              [](const Slime *s)
                                              { return s->isDefeated(); });
            if (defeatedSlime != slimes.end())
            {
                int healAmount = (*defeatedSlime)->getMaxHP() / 2; // Heal for half of max HP
                (*defeatedSlime)->heal(healAmount);
                std::cout << (*defeatedSlime)->getName() << " has been revived with "
                          << healAmount << " HP!" << std::endl;
            }
            else
            {
                std::cout << "No defeated slime to revive!" << std::endl;
                return false; // Potion wasn't actually used
            }
        }
        return true;
    }
    return false;
}

bool Player::canUseRevivalPotion() const
{
    return canUseRevivalNextTurn;
}

void Player::setCanUseRevivalPotion(bool can)
{
    canUseRevivalNextTurn = can;
}