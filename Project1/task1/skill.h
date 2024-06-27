#pragma once
#include <string>

/**
 * @brief Enumeration of possible skill types in the game.
 */
enum class SkillType
{
    Normal, /**< Normal type skill */
    Grass,  /**< Grass type skill */
    Fire,   /**< Fire type skill */
    Water   /**< Water type skill */
};

/**
 * @class Skill
 * @brief Represents a skill that can be used by slimes in battle.
 *
 * This class encapsulates the properties of a skill, including its name,
 * type, power, accuracy, and priority.
 */
class Skill
{
public:
    /**
     * @brief Constructs a new Skill.
     * @param name The name of the skill.
     * @param type The type of the skill (Normal, Grass, Fire, or Water).
     * @param power The power of the skill, determining its damage potential.
     * @param accuracy The accuracy of the skill, affecting its hit chance.
     * @param priority The priority of the skill, determining its execution order.
     */
    Skill(const std::string &name, SkillType type, int power, int accuracy, int priority);

    /**
     * @brief Gets the name of the skill.
     * @return The name of the skill.
     */
    std::string getName() const;

    /**
     * @brief Gets the type of the skill.
     * @return The SkillType of the skill.
     */
    SkillType getType() const;

    /**
     * @brief Gets the power of the skill.
     * @return The power value of the skill.
     */
    int getPower() const;

    /**
     * @brief Gets the accuracy of the skill.
     * @return The accuracy value of the skill.
     */
    int getAccuracy() const;

    /**
     * @brief Gets the priority of the skill.
     * @return The priority value of the skill.
     */
    int getPriority() const;

private:
    std::string name; /**< The name of the skill */
    SkillType type;   /**< The type of the skill */
    int power;        /**< The power of the skill */
    int accuracy;     /**< The accuracy of the skill */
    int priority;     /**< The priority of the skill */
};