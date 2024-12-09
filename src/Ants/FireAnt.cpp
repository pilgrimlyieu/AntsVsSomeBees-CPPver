#include "FireAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief 构造一个新的 FireAnt
 *
 * 默认 FireAnt 的属性：
 *
 * - 类名 name 为 "Fire"
 *
 * - 伤害 damage 为 3.0
 *
 * - 食物消耗 foodCost 为 5
 *
 * @param health FireAnt 的初始生命值，默认为 3.0
 */
FireAnt::FireAnt(double health)
    : Ant(health, {
                      {
                       .damage = 3.0,
                       },
                      .name = "FireAnt",
                      .foodCost = 5,
}) {}

/**
 * @brief 减少 FireAnt 的生命值
 *
 * 减少 FireAnt 的生命值，并在生命值小于等于 0 时使 FireAnt 死亡。
 *
 * FireAnt 在受到伤害时，会对其所在的 Place 中的所有 Bee 造成伤害。
 *
 * @param amount 要减少的生命值
 */
void FireAnt::reduceHealth(double amount) {
    double totalDamage = amount + ((amount >= health) ? damage : 0);
    bee_list killedBees;
    for (Bee *bee : place->bees) {
        if (bee->health <= totalDamage) {
            killedBees.push_back(bee);
        } else {
            bee->reduceHealth(damage);
        }
    }
    for (Bee *bee : killedBees) {
        bee->reduceHealth(totalDamage);
    }
    Insect::reduceHealth(amount);
}