#include "NinjaAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief Executes the action of the NinjaAnt.
 *
 * NinjaAnt damages all bees in its place.
 *
 * @param gamestate The current state of the game.
 */
void NinjaAnt::action(GameState &gamestate) {
    vector<Bee *> killedBees;
    for (Bee *bee : place->bees) {
        if (bee->health <= damage) {
            killedBees.push_back(bee);
        } else {
            bee->reduceHealth(damage);
        }
    }
    for (Bee *bee : killedBees) {
        bee->reduceHealth(damage);
    }
}