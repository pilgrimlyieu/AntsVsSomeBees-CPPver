#include "NinjaAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief 构造一个新的 NinjaAnt
 *
 * 默认 NinjaAnt 的属性：
 *
 * - 类名 name 为 "Ninja"
 *
 * - 伤害 damage 为 1.0
 *
 * - 食物消耗 foodCost 为 5
 *
 * @param health NinjaAnt 的初始生命值，默认为 1.0
 */
NinjaAnt::NinjaAnt(double health)
    : Ant(health, {
                      {
                       .damage = 1.0,
                       },
                      .name = "NinjaAnt",
                      .foodCost = 5,
                      .blocksPath = false,
}) {}

/**
 * @brief 执行 NinjaAnt 的动作
 *
 * NinjaAnt 的动作是对当前位置的所有 Bee 造成伤害。
 */
void NinjaAnt::action(GameState &gamestate) {
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
        bee->reduceHealth(damage);
    }
}