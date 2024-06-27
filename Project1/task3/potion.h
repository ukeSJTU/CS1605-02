/**
 * @class Potion
 * @brief Represents a potion that can be used in the game.
 */
class Potion
{
public:
    enum class Type
    {
        Revival,
        Attack
    };

    Potion(Type type) : type(type), used(false) {}

    Type getType() const { return type; }
    bool isUsed() const { return used; }
    void use() const { used = true; }

private:
    Type type;
    mutable bool used; // NOTE: mutable is decalred here so property used can be changed in a const method
};