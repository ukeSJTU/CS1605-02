#pragma once
/**
 * @class Potion
 * @brief Represents a potion that can be used in the game.
 */
class Potion
{
public:
    /**
     * @enum Type
     * @brief Defines the types of potions available in the game.
     */
    enum class Type
    {
        Revival, ///< Potion that can revive a defeated slime.
        Attack   ///< Potion that can boost a slime's attack power.
    };

    /**
     * @brief Constructs a new Potion object.
     * @param type The type of the potion.
     */
    Potion(Type type) : type(type), used(false) {}

    /**
     * @brief Get the type of the potion.
     * @return The Type of the potion.
     */
    Type getType() const { return type; }

    /**
     * @brief Check if the potion has been used.
     * @return true if the potion has been used, false otherwise.
     */
    bool isUsed() const { return used; }

    /**
     * @brief Mark the potion as used.
     * @note This method is const but modifies the mutable 'used' member.
     */
    void use() const { used = true; }

private:
    Type type;         ///< The type of the potion.
    mutable bool used; ///< Tracks whether the potion has been used.
                       ///< @note mutable is declared here so the 'used' property can be changed in a const method.
};