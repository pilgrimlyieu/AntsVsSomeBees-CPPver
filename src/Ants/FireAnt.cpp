#include "FireAnt.hpp"
#include "Bee.hpp"
#include "Place.hpp"

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
    double totalDamage = amount + ((amount >= health) ? getDamage() : 0);
    if (place->bees.size() > 0) {
        log(LOGINFO, format("{} attacks all bees in {}", this, place));
        bees_list beesToDamage(place->bees);
        for (auto bee : beesToDamage) {
            if (bee->health > 0) {
                bee->reduceHealth(totalDamage);
            }
        }
    }
    Insect::reduceHealth(amount);
}