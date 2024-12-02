#include "ThrowerAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief the nearest bee within the specified range.
 *
 * This function searches for the nearest bee within the range defined by
 * `minRange` and `maxRange` from the current place of the ThrowerAnt.
 *
 * It starts from the current place and moves towards the hive, checking
 * each place for bees.
 *
 * If a bee is found within the specified range, it
 * returns a pointer to a randomly selected bee from that place.
 *
 * @return A pointer to a Bee object if a bee is found within the range, otherwise returns nullptr.
 */
Bee *ThrowerAnt::nearestBee() {
    Place *place = this->place;
    int distance = 0;
    while (!place->isHive) {
        if (place->bees.size() > 0 && distance >= minRange && distance <= maxRange) {
            return place->randomBee();
        }
        distance++;
        place = place->entrance;
    }
    return nullptr;
}

/**
 * @brief Throws an attack at the specified target bee.
 *
 * This function reduces the health of the target bee by the damage amount
 * if the target is not a null pointer.
 *
 * @param target A pointer to the Bee object that will be attacked.
 */
void ThrowerAnt::throwAt(Bee *target) {
    if (target != nullptr) {
        target->reduceHealth(damage);
    }
}

/**
 * @brief Executes the action of the ThrowerAnt.
 *
 * This function performs the action of the ThrowerAnt by throwing at the nearest bee.
 *
 * @param gamestate The current state of the game.
 */
void ThrowerAnt::action(GameState &gamestate) {
    throwAt(nearestBee());
}