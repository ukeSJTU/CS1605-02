#pragma once
#include <vector>
#include "slime.h"
#include "strategy.h"
#include "potion.h"

class Engine;

/**
 * @class Player
 * @brief Represents a player in the game, managing their slimes and decision-making strategy.
 *
 * This class encapsulates the player's slimes, active slime, and strategy for making decisions.
 * It provides methods for choosing actions, managing slimes, and interacting with the game engine.
 */
class Player
{
public:
    /**
     * @brief Constructs a new Player with the given strategy.
     * @param strategy Pointer to the Strategy object that will guide the player's decisions.
     */
    Player(Strategy *strategy);

    /**
     * @brief Destructor for the Player class.
     * Responsible for cleaning up dynamically allocated resources.
     */
    ~Player();

    /**
     * @brief Adds a slime to the player's collection.
     * @param slime Pointer to the Slime object to be added.
     */
    void addSlime(Slime *slime);

    /**
     * @brief Sets the active slime for the player.
     * @param slime Pointer to the Slime object to be set as active.
     */
    void setActiveSlime(Slime *slime);

    /**
     * @brief Chooses an action for the player based on the current game state.
     * @param engine Reference to the Engine object representing the current game state.
     * @return The chosen Action object.
     */
    Action chooseAction(const Engine &engine);

    /**
     * @brief Chooses the starting slime for the player at the beginning of the game.
     * @param engine Reference to the Engine object representing the current game state.
     * @return Pointer to the chosen starting Slime object.
     */
    Slime *chooseStartingSlime(const Engine &engine);

    /**
     * @brief Chooses the next slime for the player when switching is necessary.
     * @param engine Reference to the Engine object representing the current game state.
     * @return Pointer to the chosen next Slime object.
     */
    Slime *chooseNextSlime(const Engine &engine);

    /**
     * @brief Gets the player's currently active slime.
     * @return Pointer to the active Slime object.
     */
    Slime *getActiveSlime() const;

    /**
     * @brief Gets a const reference to the vector of all the player's slimes.
     * @return Const reference to the vector of Slime pointers.
     */
    const std::vector<Slime *> &getSlimes() const;

    /**
     * @brief Checks if the player is defeated (all slimes are defeated).
     * @return true if the player is defeated, false otherwise.
     */
    bool isDefeated() const;

    void addPotion(const Potion &potion);
    const std::vector<Potion> &getPotions() const;
    bool usePotion(Potion::Type type, Slime *target);
    bool canUseRevivalPotion() const;
    void setCanUseRevivalPotion(bool can);

private:
    std::vector<Slime *> slimes; /**< Vector of pointers to the player's Slime objects */
    Slime *activeSlime;          /**< Pointer to the currently active Slime */
    Strategy *strategy;          /**< Pointer to the Strategy object guiding the player's decisions */

    std::vector<Potion> potions;
    bool canUseRevivalNextTurn = false;
};