#pragma once

/**
 * @brief Enumeration of possible action types in the game.
 */
enum class ActionType
{
    UseSkill,    /**< Use a skill during the turn */
    ChangeSlime, /**< Change the active slime during the turn */
    UsePotion    /**< Use a potion during the turn */
};

/**
 * @class Action
 * @brief Represents an action taken by a player during their turn.
 *
 * This class encapsulates the type of action, the index of the skill or slime involved,
 * and the priority of the action.
 */
class Action
{
public:
    /**
     * @brief Constructs a new Action.
     * @param type The type of the action (UseSkill or ChangeSlime).
     * @param index The index of the skill or slime, depending on the action type.
     * @param priority The priority of the action, used to determine execution order.
     */
    Action(ActionType type, int index, int priority);

    /**
     * @brief Get the type of the action.
     * @return The ActionType of this action.
     */
    ActionType getType() const;

    /**
     * @brief Get the index associated with this action.
     * @return The index of the skill or slime, depending on the action type.
     */
    int getIndex() const;

    /**
     * @brief Get the priority of the action.
     * @return The priority value of this action.
     */
    int getPriority() const;

private:
    ActionType type; /**< The type of the action */
    int index;       /**< The index of the skill or slime */
    int priority;    /**< The priority of the action */
};