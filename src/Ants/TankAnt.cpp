#include "TankAnt.hpp"
#include "Bee.hpp"
#include "GameState.hpp"
#include "Place.hpp"

/**
 * @brief 执行 TankAnt 的动作
 *
 * TankAnt 的动作是对所有当前 Place 中的 Bee 造成伤害。
 *
 * 同时会执行身为 ContainerAnt 的动作。
 */
void TankAnt::action(GameState &gamestate) {
    log(LOGINFO, format("{} attacks all bees in {}", *this, *place));
    std::erase_if(place->bees, [&](auto &bee) {
        bee->reduceHealth(getDamage());
        return bee->health <= 0;
    });
    ContainerAnt::action(gamestate);
}