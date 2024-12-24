#include "TankAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief 构造一个新的 TankAnt
 *
 * @param health TankAnt 的初始生命值，默认为 2
 */
TankAnt::TankAnt(double health)
    : ContainerAnt(health, {
                               {
                                {
                                       .damage = 1.0,
                                   }, .foodCost = 6,
                                },
                               .name = "TankAnt",
}) {}

/**
 * @brief 执行 TankAnt 的动作
 *
 * TankAnt 的动作是对所有当前 Place 中的 Bee 造成伤害。
 *
 * 同时会执行身为 ContainerAnt 的动作。
 */
void TankAnt::action(GameState &gamestate) {
    bee_list killedBees;
    for (Bee *bee : place->bees) {
        if (bee->health <= damage) {
            killedBees.push_back(bee);
        } else {
            bee->reduceHealth(damage);
        }
        log(LOGINFO, format("{} attacks {}", string(*this), string(*bee)));
    }
    for (Bee *bee : killedBees) {
        bee->reduceHealth(bee->health);
    }
    ContainerAnt::action(gamestate);
}