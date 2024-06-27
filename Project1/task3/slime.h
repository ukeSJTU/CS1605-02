#pragma once
#include <string>
#include <vector>
#include "skill.h"

/**
 * @brief Enumeration of possible slime types in the game.
 */
enum class SlimeType
{
    Grass, /**< Grass type slime */
    Fire,  /**< Fire type slime */
    Water  /**< Water type slime */
};

/**
 * @class Slime
 * @brief Represents a slime character in the game.
 *
 * This class encapsulates the properties and behaviors of a slime,
 * including its stats, skills, and battle-related methods.
 */
class Slime
{
public:
    /**
     * @brief Constructs a new Slime.
     * @param name The name of the slime.
     * @param type The type of the slime (Grass, Fire, or Water).
     * @param maxHP The maximum hit points of the slime.
     * @param attack The attack stat of the slime.
     * @param defense The defense stat of the slime.
     * @param speed The speed stat of the slime.
     */
    Slime(const std::string &name, SlimeType type, int maxHP, int attack, int defense, int speed);

    /**
     * @brief Gets the name of the slime.
     * @return The name of the slime.
     */
    std::string getName() const;

    /**
     * @brief Gets the type of the slime.
     * @return The SlimeType of the slime.
     */
    SlimeType getType() const;

    /**
     * @brief Gets the current hit points of the slime.
     * @return The current HP of the slime.
     */
    int getCurrentHP() const;

    /**
     * @brief Gets the maximum hit points of the slime.
     * @return The max HP of the slime.
     */
    int getMaxHP() const;

    /**
     * @brief Gets the attack stat of the slime.
     * @return The attack value of the slime.
     */
    int getAttack() const;

    /**
     * @brief Gets the defense stat of the slime.
     * @return The defense value of the slime.
     */
    int getDefense() const;

    /**
     * @brief Gets the speed stat of the slime.
     * @return The speed value of the slime.
     */
    int getSpeed() const;

    /**
     * @brief Gets the skills of the slime.
     * @return A const reference to the vector of Skills.
     */
    const std::vector<Skill> &getSkills() const;

    /**
     * @brief Applies damage to the slime.
     * @param damage The amount of damage to be taken.
     */
    void takeDamage(int damage);

    /**
     * @brief Checks if the slime is defeated (HP <= 0).
     * @return true if the slime is defeated, false otherwise.
     */
    bool isDefeated() const;

    /**
     * @brief Heals the slime by the specified amount.
     * @param amount The amount of HP to heal.
     */
    void heal(int amount);

    void boostAttack() { attackBoosted = true; }
    void resetAttackBoost() { attackBoosted = false; }
    bool isAttackBoosted() const { return attackBoosted; }

private:
    std::string name;          /**< The name of the slime */
    SlimeType type;            /**< The type of the slime */
    int maxHP;                 /**< The maximum hit points of the slime */
    int currentHP;             /**< The current hit points of the slime */
    int attack;                /**< The attack stat of the slime */
    int defense;               /**< The defense stat of the slime */
    int speed;                 /**< The speed stat of the slime */
    std::vector<Skill> skills; /**< The skills possessed by the slime */
    bool attackBoosted = false;
};