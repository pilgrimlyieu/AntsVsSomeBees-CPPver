#include "NinjaAnt.hpp"
#include "Bee.hpp"
#include "Place.hpp"

/**
 * @brief 执行 NinjaAnt 的动作
 *
 * NinjaAnt 的动作是对当前位置的所有 Bee 造成伤害。
 */
void NinjaAnt::action(GameState &gamestate) {
    if (place->bees.size() > 0) {
        log(LOGINFO, format("{} attacks all bees in {}", this, place));
        bees_list beesToDamage(place->bees);
        for (auto bee : beesToDamage) {
            if (bee->health > 0) {
                bee->reduceHealth(getDamage());
            }
        }
    }
}