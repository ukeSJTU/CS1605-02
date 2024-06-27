#include "player.h"
#include "engine.h"

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
