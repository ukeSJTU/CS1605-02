#pragma once
#include <vector>
#include "action.h"

class Engine;
class Slime;

/**
 * @class Strategy
 * @brief Abstract base class for different game strategies.
 *
 * This class defines the interface for strategies that can be used by players
 * to make decisions in the game.
 */
class Strategy
{
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Strategy() = default;

    /**
     * @brief Chooses an action based on the current game state.
     * @param engine Reference to the game engine containing the current state.
     * @return The chosen Action.
     */
    virtual Action chooseAction(const Engine &engine) = 0;

    /**
     * @brief Chooses a starting slime at the beginning of the game.
     * @param slimes Vector of available slimes to choose from.
     * @param engine Reference to the game engine containing the current state.
     * @return Pointer to the chosen starting Slime.
     */
    virtual Slime *chooseStartingSlime(const std::vector<Slime *> &slimes, const Engine &engine) = 0;

    /**
     * @brief Chooses the next slime when a switch is necessary.
     * @param slimes Vector of available slimes to choose from.
     * @param engine Reference to the game engine containing the current state.
     * @return Pointer to the chosen next Slime.
     */
    virtual Slime *chooseNextSlime(const std::vector<Slime *> &slimes, const Engine &engine) = 0;
};

/**
 * @class HumanStrategy
 * @brief Concrete strategy class for human player decisions.
 *
 * This class implements the Strategy interface for human players,
 * prompting for user input to make decisions.
 */
class HumanStrategy : public Strategy
{
private:
    /**
     * @brief Helper method to choose the index of the next slime.
     * @param slimes Vector of available slimes to choose from.
     * @param activeSlime Pointer to the currently active slime.
     * @return Index of the chosen slime in the slimes vector.
     */
    int chooseNextSlimeIndex(const std::vector<Slime *> &slimes, Slime *activeSlime);

public:
    Action chooseAction(const Engine &engine) override;
    Slime *chooseStartingSlime(const std::vector<Slime *> &slimes, const Engine &engine) override;
    Slime *chooseNextSlime(const std::vector<Slime *> &slimes, const Engine &engine) override;
};

/**
 * @class SimpleAIStrategy
 * @brief Concrete strategy class for a simple AI player.
 *
 * This class implements the Strategy interface for an AI player
 * with basic decision-making logic.
 */
class SimpleAIStrategy : public Strategy
{
public:
    Action chooseAction(const Engine &engine) override;
    Slime *chooseStartingSlime(const std::vector<Slime *> &slimes, const Engine &engine) override;
    Slime *chooseNextSlime(const std::vector<Slime *> &slimes, const Engine &engine) override;
};