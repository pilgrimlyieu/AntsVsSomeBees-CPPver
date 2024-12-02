#include "FireAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * Reduces the health of the FireAnt by the specified amount and deals damage to bees in the same
 * place.
 *
 * @param amount The amount of health to reduce from the FireAnt.
 *
 * This method calculates the total damage to be dealt, which includes an additional damage if the
 * amount is greater than or equal to the FireAnt's current health. It then iterates through all the
 * bees in the same place as the FireAnt.
 *
 * If a bee's health is less than or equal to the total damage, it is marked to be killed.
 *
 * Otherwise, the bee's health is reduced by the FireAnt's damage value.
 *
 * Finally, all marked bees have their health reduced by the total damage, and the FireAnt's health
 * is reduced by the specified amount.
 */
void FireAnt::reduceHealth(int amount) {
    int totalDamage = amount + ((amount >= health) ? damage : 0);
    vector<Bee *> killedBees;
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