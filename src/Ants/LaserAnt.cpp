#include "LaserAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief Retrieves the targets within the range of the LaserAnt.
 *
 * This function traverses the places starting from the current place of the LaserAnt
 * and collects all the ants and bees encountered along the way until it reaches the hive.
 *
 * The targets are stored in an unordered_map with the insect pointers as keys and their
 * respective distances from the LaserAnt as values.
 *
 * @return An unordered_map where the keys are pointers to Insect objects (either ants or bees)
 *         and the values are the distances of these insects from the LaserAnt.
 */
unordered_map<Insect *, int> LaserAnt::getTargets() {
    unordered_map<Insect *, int> targets;
    int distance = 0;
    Place *currentPlace = place;
    while (!currentPlace->isHive) {
        if (currentPlace->ant != nullptr && currentPlace->ant != this) {
            targets[currentPlace->ant] = distance;
        }
        for (Bee *bee : currentPlace->bees) {
            targets[bee] = distance;
        }
        currentPlace = currentPlace->entrance;
        distance++;
    }
    return targets;
}

/**
 * @brief Calculates the damage dealt by the LaserAnt based on the distance to the target and the
 * number of insects shot.
 *
 * damage = baseDamage - 0.25 * distance - insectsShot / 16
 *
 * @param distance The distance to the target.
 * @return int The calculated damage, ensuring it is not less than 0.
 */
int LaserAnt::getDamage(int distance) {
    double trueDamage = damage - 0.25 * distance - ((double)insectsShot) / 16;
    return (int)max(0.0, trueDamage);
}

/**
 * @brief Executes the action of the LaserAnt in the game.
 *
 * This function targets multiple insects within range and deals damage to them.
 *
 * The damage dealt to each insect is determined by the getDamage function.
 *
 * The number of insects shot is tracked by the insectsShot counter.
 *
 * @param gamestate The current state of the game.
 */
void LaserAnt::action(GameState &gamestate) {
    unordered_map<Insect *, int> targets = getTargets();
    for (auto &target : targets) {
        int damage = getDamage(target.second);
        target.first->reduceHealth(damage);
        if (damage > 0) {
            insectsShot++;
        }
    }
}