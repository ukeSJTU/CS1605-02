#include "engine.h"
#include "player.h"
#include "strategy.h"
#include "slime.h"
#include <iostream>

int main()
{
    HumanStrategy *humanStrategy = new HumanStrategy();
    GreedyAIStrategy *enemyStrategy = new GreedyAIStrategy();

    Player human(humanStrategy);
    Player ai(enemyStrategy);

    human.addSlime(new Slime("Green", SlimeType::Grass, 110, 10, 10, 10));
    human.addSlime(new Slime("Red", SlimeType::Fire, 100, 11, 10, 11));
    human.addSlime(new Slime("Blue", SlimeType::Water, 100, 10, 11, 9));

    ai.addSlime(new Slime("Green", SlimeType::Grass, 110, 10, 10, 10));
    ai.addSlime(new Slime("Red", SlimeType::Fire, 100, 11, 10, 11));
    ai.addSlime(new Slime("Blue", SlimeType::Water, 100, 10, 11, 9));

    Engine engine(human, ai);

    engine.startGame();
    engine.runGame();

    return 0;
}