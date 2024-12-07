#include "FireAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief 减少 FireAnt 的生命值
 *
 * 减少 FireAnt 的生命值，并在生命值小于等于 0 时使 FireAnt 死亡。
 *
 * FireAnt 在受到伤害时，会对其所在的 Place 中的所有 Bee 造成伤害。
 *
 * @param amount 要减少的生命值
 */
void FireAnt::reduceHealth(int amount) {
    double totalDamage = amount + ((amount >= health) ? damage : 0);
    std::vector<Bee *> killedBees;
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