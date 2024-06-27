#pragma once
#include "player.h"
#include <vector>

/**
 * @class Engine
 * @brief Main game engine class that manages the game state and flow.
 *
 * This class is responsible for coordinating players, managing game rounds,
 * and controlling the overall game logic.
 */
class Engine
{
public:
    /**
     * @brief Constructs a new Engine with the given players.
     * @param player The human player.
     * @param enemy The AI opponent.
     */
    Engine(Player &player, Player &enemy);

    /**
     * @brief Initializes the game, setting up initial slimes and game state.
     */
    void startGame();

    /**
     * @brief Runs the main game loop until the game is over.
     */
    void runGame();

    /**
     * @brief Checks if the game has ended.
     * @return true if the game is over, false otherwise.
     */
    bool isGameOver() const;

    /**
     * @brief Gets the current round number.
     * @return The current round number.
     */
    int getRound() const;

    /**
     * @brief Gets a const reference to the human player.
     * @return Const reference to the human player.
     */
    const Player &getPlayer() const;

    /**
     * @brief Gets a const reference to the AI opponent.
     * @return Const reference to the AI opponent.
     */
    const Player &getEnemy() const;

    /**
     * @brief Gets a pointer to the human player's active slime.
     * @return Pointer to the human player's active slime.
     */
    Slime *getPlayerActiveSlime() const;

    /**
     * @brief Gets a pointer to the AI opponent's active slime.
     * @return Pointer to the AI opponent's active slime.
     */
    Slime *getEnemyActiveSlime() const;

private:
    Player &player;           /**< Reference to the human player */
    Player &enemy;            /**< Reference to the AI opponent */
    int round;                /**< Current round number */
    Slime *playerActiveSlime; /**< Pointer to the human player's active slime */
    Slime *enemyActiveSlime;  /**< Pointer to the AI opponent's active slime */

    /**
     * @brief Updates the game state after each action or round.
     */
    void updateGameState();

    /**
     * @brief Processes a single round of the game.
     */
    void processRound();

    /**
     * @brief Executes a turn for both players.
     */
    void executeTurn();

    /**
     * @brief Executes a single action for a player.
     * @param attacker The player executing the action.
     * @param defender The opposing player.
     * @param action The action to be executed.
     * @return true if the action was successful, false otherwise.
     */
    bool executeAction(Player &attacker, Player &defender, const Action &action);

    /**
     * @brief Calculates the damage for an attack.
     * @param attacker The attacking slime.
     * @param defender The defending slime.
     * @param skill The skill being used for the attack.
     * @return The calculated damage.
     */
    int calculateDamage(const Slime &attacker, const Slime &defender, const Skill &skill);

    /**
     * @brief Determines the effectiveness multiplier based on attack and defender types.
     * @param attackType The type of the attack.
     * @param defenderType The type of the defending slime.
     * @return The effectiveness multiplier.
     */
    float getTypeEffectiveness(SkillType attackType, SlimeType defenderType);

    /**
     * @brief Displays the current status of the game.
     */
    void displayStatus() const;

    /**
     * @brief Displays the final results of the game.
     */
    void displayResults() const;

    /**
     * @brief Sets the active slimes for both players.
     * @param playerSlime Pointer to the new active slime for the human player.
     * @param enemySlime Pointer to the new active slime for the AI opponent.
     */
    void setActiveSlimes(Slime *playerSlime, Slime *enemySlime);
};