#include "QueenAnt.h"
#include "ContainerAnt.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief 构造一个新的 QueenAnt
 *
 * 默认 QueenAnt 的属性：
 *
 * - 类名 name 为 "Queen"
 *
 * - 食物消耗 foodCost 为 7
 *
 * @param health QueenAnt 的初始生命值，默认为 1.0
 */
QueenAnt::QueenAnt(double health)
    : ScubaThrower(health, {
                               .name = "QueenAnt",
                               .foodCost = 7,
                           }) {}

/**
 * @brief 执行 QueenAnt 的动作
 *
 * QueenAnt 的动作是对当前位置的所有 Bee 造成伤害，并对所有出口方向的 Ant
 * 加成。
 */
void QueenAnt::action(GameState &gamestate) {
    ThrowerAnt::action(gamestate);
    Place *currentPlace = place->exit;
    while (currentPlace != nullptr) {
        Ant *ant = currentPlace->ant;
        if (ant != nullptr) {
            ant->buff();
            if (ant->isContainer && ((ContainerAnt *)ant)->antContained != nullptr) {
                ((ContainerAnt *)ant)->antContained->buff();
            }
        }
        currentPlace = currentPlace->exit;
    }
}

/**
 * @brief 减少 QueenAnt 的生命值
 *
 * 减少 QueenAnt 的生命值，并在生命值小于等于 0 时结束游戏。
 *
 * @param amount 要减少的生命值
 */
void QueenAnt::reduceHealth(double amount) {
    health -= amount;
    if (health <= 0.0) {
        antsLose();
    }
}

/**
 * @brief 从指定的 Place 中移除 QueenAnt
 *
 * QueenAnt 死亡时结束游戏，因此不需要从 Place 中移除 QueenAnt 。
 *
 * @param place 指向要移除的 Place 的指针
 */
void QueenAnt::removeFrom(Place *place) {
    // Do nothing because game ends when QueenAnt dies
}