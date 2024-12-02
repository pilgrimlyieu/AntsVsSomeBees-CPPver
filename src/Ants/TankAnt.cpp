#include "TankAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Constructs a new TankAnt object with the specified health.
 *
 * @param health The initial health of the TankAnt. Defaults to 2.
 */
TankAnt::TankAnt(int health) : ContainerAnt(health) {}

/**
 * @brief Executes the action of the TankAnt.
 *
 * This method iterates through all the bees in the current place of the TankAnt.
 *
 * The TankAnt deals damage to each bee in the place, and do the action of the ContainerAnt.
 *
 * @param gamestate The current state of the game.
 */
void TankAnt::action(GameState &gamestate) {
    vector<Bee *> killedBees;
    for (Bee *bee : place->bees) {
        if (bee->health <= damage) {
            killedBees.push_back(bee);
        } else {
            bee->reduceHealth(damage);
        }
    }
    for (Bee *bee : killedBees) {
        bee->reduceHealth(bee->health);
    }
    ContainerAnt::action(gamestate);
}