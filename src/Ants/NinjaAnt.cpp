#include "NinjaAnt.hpp"
#include "Bee.hpp"
#include "Place.hpp"

/**
 * @brief 执行 NinjaAnt 的动作
 *
 * NinjaAnt 的动作是对当前位置的所有 Bee 造成伤害。
 */
void NinjaAnt::action(GameState &gamestate) {
    log(LOGINFO, format("{} attacks all bees in {}", *this, *place));
    std::erase_if(place->bees, [&](auto &bee) {
        bee->reduceHealth(getDamage());
        return bee->health <= 0;
    });
}