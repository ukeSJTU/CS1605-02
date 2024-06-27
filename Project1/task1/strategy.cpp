#include "strategy.h"
#include "engine.h"
#include "slime.h"
#include <iostream>
#include <vector>
#include <random>

int HumanStrategy::chooseNextSlimeIndex(const std::vector<Slime *> &slimes, Slime *activeSlime)
{
    std::vector<int> validChoices;

    // find all valid choices
    for (size_t i = 0; i < slimes.size(); ++i)
    {
        if (!slimes[i]->isDefeated() && slimes[i] != activeSlime)
        {
            validChoices.push_back(i);
        }
    }

    while (true)
    {
        std::cout << "Select your next slime (";
        for (size_t i = 0; i < validChoices.size(); ++i)
        {
            std::cout << validChoices[i] + 1 << " for " << slimes[validChoices[i]]->getName();
            if (i < validChoices.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "): ";

        int choice;
        std::cin >> choice;
        choice = choice - 1; // Convert to 0-based index

        // check if user's input index is valid
        auto it = std::find(validChoices.begin(), validChoices.end(), choice);
        if (it != validChoices.end())
        {
            return choice;
        }
    }
}

Action HumanStrategy::chooseAction(const Engine &engine)
{
    const std::vector<Slime *> &slimes = engine.getPlayer().getSlimes();
    Slime *activeSlime = engine.getPlayerActiveSlime();
    bool hasAliveInactiveSlimes = false;

    // check if player has any other slime that is not defeated
    for (const auto &slime : slimes)
    {
        if (!slime->isDefeated() && slime != activeSlime)
        {
            hasAliveInactiveSlimes = true;
            break;
        }
    }

    int choice = 0;
    if (hasAliveInactiveSlimes)
    {
        // if user's input is not in range, ask again until it is
        while (choice < 1 || choice > 2)
        {
            std::cout << "Select your action: (1 for skill, 2 for change): ";
            std::cin >> choice;
        }
    }
    else
    {
        // if player does not have any other slime to change to, only allow skill
        while (choice != 1)
        {
            std::cout << "Select your action: (1 for skill): ";
            std::cin >> choice;
        }
    }

    if (choice == 1)
    {
        // if user's input is not in range, ask again until it is
        int skillIndex = 0;
        while (skillIndex < 1 || skillIndex > 2)
        {
            std::cout << "Select the skill (1 for Tackle, 2 for "
                      << engine.getPlayerActiveSlime()->getSkills()[1].getName() << "): ";
            std::cin >> skillIndex;
        }
        skillIndex = skillIndex - 1; // skillIndex is 0-based
        return Action(ActionType::UseSkill, skillIndex, 0);
    }

    else
    {
        int slimeIndex = chooseNextSlimeIndex(slimes, activeSlime);
        return Action(ActionType::ChangeSlime, slimeIndex, 6);
    }
}

Slime *HumanStrategy::chooseStartingSlime(const std::vector<Slime *> &slimes, const Engine &engine)
{
    int choice = 0;
    // if user's input is not in range, ask again until it is
    while (choice < 1 || choice > 3)
    {
        std::cout << "Select your starting slime (1 for Green, 2 for Red, 3 for Blue): ";
        std::cin >> choice;
    }
    return slimes[choice - 1]; // index is 0-based
}

Slime *HumanStrategy::chooseNextSlime(const std::vector<Slime *> &slimes, const Engine &engine)
{
    Slime *activeSlime = engine.getPlayerActiveSlime();
    int slimeIndex = chooseNextSlimeIndex(slimes, activeSlime);
    return slimes[slimeIndex];
}

Action SimpleAIStrategy::chooseAction(const Engine &engine)
{
    // simple ai controlled enemy won't change slime during battle unless their current one dies and is forced to choose a new slime
    // if enemy's current slime has type advantage(effectiveness) over player's current slime, use skill 2
    // else, always use skill 1
    const Slime *slime = engine.getEnemyActiveSlime(); // enemy's slime
    const Slime *playerCurrentSlime = engine.getPlayerActiveSlime();
    if ((slime->getType() == SlimeType::Water && playerCurrentSlime->getType() == SlimeType::Fire) ||
        (slime->getType() == SlimeType::Fire && playerCurrentSlime->getType() == SlimeType::Grass) ||
        (slime->getType() == SlimeType::Grass && playerCurrentSlime->getType() == SlimeType::Water))
    {
        return Action(ActionType::UseSkill, 1, 0); // skill 2, 0-based
    }
    else
    {
        return Action(ActionType::UseSkill, 0, 0); // skill 1, 0-based
    }
}

Slime *SimpleAIStrategy::chooseStartingSlime(const std::vector<Slime *> &slimes, const Engine &engine)
{
    // Simple AI chooses a slime that has type advantage over the player's starting slime
    Slime *playerSlime = engine.getPlayerActiveSlime();
    for (Slime *slime : slimes)
    {
        if ((slime->getType() == SlimeType::Water && playerSlime->getType() == SlimeType::Fire) ||
            (slime->getType() == SlimeType::Fire && playerSlime->getType() == SlimeType::Grass) ||
            (slime->getType() == SlimeType::Grass && playerSlime->getType() == SlimeType::Water))
        {
            return slime;
        }
    }
    // If no strong matchup, choose randomly
    // NOTE: in real case, this would not happen, enemy will always have one slime that has type advantage over player's starting slime
    return slimes[rand() % slimes.size()];
}

Slime *SimpleAIStrategy::chooseNextSlime(const std::vector<Slime *> &slimes, const Engine &engine)
{
    const Slime *playerCurrentSlime = engine.getPlayerActiveSlime();

    Slime *enemyRedSlime = nullptr;
    Slime *enemyBlueSlime = nullptr;
    Slime *enemyGreenSlime = nullptr;

    for (Slime *slime : slimes)
    {
        switch (slime->getType())
        {
        case SlimeType::Fire:
            enemyRedSlime = slime;
            break;
        case SlimeType::Water:
            enemyBlueSlime = slime;
            break;
        case SlimeType::Grass:
            enemyGreenSlime = slime;
            break;
        }
    }

    // choose the one that has type advantage, if not, choose the one that is the same with player's current slime
    if (playerCurrentSlime->getType() == SlimeType::Water)
    {
        if (enemyGreenSlime && !enemyGreenSlime->isDefeated())
        {
            return enemyGreenSlime;
        }
        else if (enemyBlueSlime && !enemyBlueSlime->isDefeated())
        {
            return enemyBlueSlime;
        }
    }

    else if (playerCurrentSlime->getType() == SlimeType::Fire)
    {
        if (enemyBlueSlime && !enemyBlueSlime->isDefeated())
        {
            return enemyBlueSlime;
        }
        else if (enemyRedSlime && !enemyRedSlime->isDefeated())
        {
            return enemyRedSlime;
        }
    }

    else if (playerCurrentSlime->getType() == SlimeType::Grass)
    {
        if (enemyRedSlime && !enemyRedSlime->isDefeated())
        {
            return enemyRedSlime;
        }
        else if (enemyGreenSlime && !enemyGreenSlime->isDefeated())
        {
            return enemyGreenSlime;
        }
    }

    // iterate and find the last one slime which is not defeated.
    for (Slime *slime : slimes)
    {
        if (!slime->isDefeated())
        {
            return slime;
        }
    }
}