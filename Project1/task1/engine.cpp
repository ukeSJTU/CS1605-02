#include "engine.h"
#include <iostream>
#include <cmath>

Engine::Engine(Player &player, Player &enemy)
    : player(player), enemy(enemy), round(0), playerActiveSlime(nullptr), enemyActiveSlime(nullptr) {}

void Engine::startGame()
{
    std::cout << "Welcome to Battle of Slimes!" << std::endl;
    std::cout << "You have Green, Red and Blue. So does Enemy." << std::endl;

    playerActiveSlime = player.chooseStartingSlime(*this);
    enemyActiveSlime = enemy.chooseStartingSlime(*this);

    std::cout << "You start with " << playerActiveSlime->getName() << std::endl;
    std::cout << "Enemy starts with " << enemyActiveSlime->getName() << std::endl;

    player.setActiveSlime(playerActiveSlime);
    enemy.setActiveSlime(enemyActiveSlime);
    updateGameState();

    std::cout << "Battle starts!" << std::endl;
}

void Engine::runGame()
{
    while (true)
    {
        processRound();
        if (isGameOver())
        {
            break;
        }
        updateGameState();
    }
    displayResults();
}

bool Engine::isGameOver() const
{
    return player.isDefeated() || enemy.isDefeated() || round >= 100;
}

int Engine::getRound() const { return round; }
const Player &Engine::getPlayer() const { return player; }
const Player &Engine::getEnemy() const { return enemy; }
Slime *Engine::getPlayerActiveSlime() const { return playerActiveSlime; }
Slime *Engine::getEnemyActiveSlime() const { return enemyActiveSlime; }

void Engine::updateGameState()
{
    round++;
    displayStatus();
}

void Engine::processRound()
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Round " << round << std::endl;
    executeTurn();
    // updateGameState();
}

void Engine::executeTurn()
{
    Action playerAction = player.chooseAction(*this);
    Action enemyAction = enemy.chooseAction(*this);

    bool isNextMoveSlimeKilled = false;

    // if player's action has higher priority, execute player's action first
    if (playerAction.getPriority() > enemyAction.getPriority())
    {
        isNextMoveSlimeKilled = executeAction(player, enemy, playerAction);
        if (!isNextMoveSlimeKilled)
        {
            executeAction(enemy, player, enemyAction);
        }
    }
    // if player's action has the same priority as enemy's action
    else if (playerAction.getType() == ActionType::ChangeSlime && enemyAction.getType() == ActionType::ChangeSlime)
    {
        // if player and enemy choose to change their slime, both actions are executed at the same time, so no one knows the other one's next slime.
        // in order to display player's info before enemy's, execute player's action first
        isNextMoveSlimeKilled = executeAction(player, enemy, playerAction);
        if (!isNextMoveSlimeKilled)
        {
            executeAction(enemy, player, enemyAction);
        }
    }
    else if (playerAction.getPriority() == enemyAction.getPriority())
    {
        // if player and enemy choose to use skill, the one with higher speed will execute the action first
        if (player.getActiveSlime()->getSpeed() > enemy.getActiveSlime()->getSpeed())
        {
            isNextMoveSlimeKilled = executeAction(player, enemy, playerAction);
            if (!isNextMoveSlimeKilled)
            {
                executeAction(enemy, player, enemyAction);
            }
        }
        // if player's action is the same priority as enemy's action, but enemy's slime has higher or equal speed, execute enemy's action first
        else
        {
            isNextMoveSlimeKilled = executeAction(enemy, player, enemyAction);
            if (!isNextMoveSlimeKilled)
            {
                executeAction(player, enemy, playerAction);
            }
        }
    }
    // if enemy's action has higher priority, execute enemy's action first
    else
    {
        isNextMoveSlimeKilled = executeAction(enemy, player, enemyAction);
        if (!isNextMoveSlimeKilled)
        {
            executeAction(player, enemy, playerAction);
        }
    }
}

bool Engine::executeAction(Player &attacker, Player &defender, const Action &action)
{
    switch (action.getType())
    {
    case ActionType::UseSkill:
    {
        Slime *attackerSlime = attacker.getActiveSlime();
        Slime *defenderSlime = defender.getActiveSlime();
        const Skill &skill = attackerSlime->getSkills()[action.getIndex()];

        int damage = calculateDamage(*attackerSlime, *defenderSlime, skill);
        defenderSlime->takeDamage(damage);

        if (&attacker == &player)
        {
            // if player is the attacker
            std::cout << "Your ";
        }
        else
        {
            // if enemy is the attacker
            std::cout << "Enemy's ";
        }
        std::cout << attackerSlime->getName() << " uses " << skill.getName() << "! Damage: " << damage << std::endl;

        if (defenderSlime->isDefeated())
        {
            if (&defender == &player)
            {
                // if player is the defender
                std::cout << "Your ";
            }
            else
            {
                // if enemy is the defender
                std::cout << "Enemy's ";
            }
            std::cout << defenderSlime->getName() << " is beaten" << std::endl;

            // if the last slime is killed and the game is not over, the player should choose the next slime
            if (isGameOver())
            {
                return true; // go back to executeTurn() and display the result
            }
            Slime *nextSlime = defender.chooseNextSlime(*this);

            if (nextSlime)
            {
                defender.setActiveSlime(nextSlime);
                if (&defender == &player)
                {
                    // if player is the defender
                    setActiveSlimes(nextSlime, enemyActiveSlime);
                    std::cout << "You send ";
                }
                else
                {
                    // if enemy is the defender
                    setActiveSlimes(playerActiveSlime, nextSlime);
                    std::cout << "Enemy sends ";
                }
                std::cout << defender.getActiveSlime()->getName() << std::endl;
            }

            return true; // a forced change of slime means that the opponent's current slime is killed and this should forbid that player (either attacker or defender) from using skill
        }
        break;
    }
    case ActionType::ChangeSlime:
    {
        Slime *newSlime = attacker.getSlimes()[action.getIndex()];
        attacker.setActiveSlime(newSlime);
        if (&attacker == &player)
        {
            setActiveSlimes(newSlime, enemyActiveSlime);
            std::cout << "You send ";
        }
        else
        {
            setActiveSlimes(playerActiveSlime, newSlime);
            std::cout << "Enemy sends ";
        }
        std::cout << attacker.getActiveSlime()->getName() << std::endl;
        break;
    }
    }
    return false;
}

int Engine::calculateDamage(const Slime &attacker, const Slime &defender, const Skill &skill)
{
    float effectiveness = getTypeEffectiveness(skill.getType(), defender.getType());
    float damage = (skill.getPower() * attacker.getAttack() / defender.getDefense()) * effectiveness;
    return std::max(1, static_cast<int>(std::round(damage)));
}

float Engine::getTypeEffectiveness(SkillType attackType, SlimeType defenderType)
{
    if (attackType == SkillType::Grass && defenderType == SlimeType::Water)
        return 2.0f;
    if (attackType == SkillType::Fire && defenderType == SlimeType::Grass)
        return 2.0f;
    if (attackType == SkillType::Water && defenderType == SlimeType::Fire)
        return 2.0f;
    if (attackType == SkillType::Grass && defenderType == SlimeType::Fire)
        return 0.5f;
    if (attackType == SkillType::Fire && defenderType == SlimeType::Water)
        return 0.5f;
    if (attackType == SkillType::Water && defenderType == SlimeType::Grass)
        return 0.5f;
    if (attackType == SkillType::Grass && defenderType == SlimeType::Grass)
        return 0.5f;
    if (attackType == SkillType::Fire && defenderType == SlimeType::Fire)
        return 0.5f;
    if (attackType == SkillType::Water && defenderType == SlimeType::Water)
        return 0.5f;
    return 1.0f;
}

void Engine::displayStatus() const
{
    std::cout << "Your " << playerActiveSlime->getName() << ": HP " << playerActiveSlime->getCurrentHP() << " || Enemy's " << enemyActiveSlime->getName() << ": HP " << enemyActiveSlime->getCurrentHP() << std::endl;
    return;
}

void Engine::displayResults() const
{
    if (player.isDefeated())
    {
        std::cout << "You Lose" << std::endl;
    }
    else if (enemy.isDefeated())
    {
        std::cout << "You Win" << std::endl;
    }
    else
    {
        std::cout << "Draw" << std::endl;
    }
}

void Engine::setActiveSlimes(Slime *playerSlime, Slime *enemySlime)
{
    playerActiveSlime = playerSlime;
    enemyActiveSlime = enemySlime;
}