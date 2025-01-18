#include "QueenAnt.hpp"
#include "ContainerAnt.hpp"
#include "GameState.hpp"
#include "Place.hpp"

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
            auto container_ptr = dynamic_cast<ContainerAnt *>(ant);
            if (container_ptr && container_ptr->antContained != nullptr) {
                container_ptr->antContained->buff();
            }
        }
        currentPlace = currentPlace->exit;
    }
    log(LOGINFO, format("{} performs its action", *this));
}

/**
 * @brief 减少 QueenAnt 的生命值
 *
 * 减少 QueenAnt 的生命值，并在生命值小于等于 0 时结束游戏。
 *
 * @param amount 要减少的生命值
 */
void QueenAnt::reduceHealth(double amount) {
    Insect::reduceHealth(amount);
    if (health <= 0.0) {
        antsLose();
    }
}
