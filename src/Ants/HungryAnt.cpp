#include "HungryAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Constructs a new HungryAnt object with the specified health.
 *
 * This constructor initializes a HungryAnt object by calling the base class
 * Ant constructor with the given health value. Additionally, it initializes
 * the chewCountDown member to 0.
 *
 * @param health The initial health value for the HungryAnt. Default value is 1.
 */
HungryAnt::HungryAnt(int health) : Ant(health), chewCountDown(0) {}

/**
 * @brief Executes the action of the HungryAnt.
 *
 * The HungryAnt will attempt to eat a random bee in its place if it is not currently chewing.
 *
 * If the HungryAnt is chewing, it will decrement its chew countdown.
 *
 * @param gamestate The current state of the game.
 */
void HungryAnt::action(GameState &gamestate) {
    if (chewCountDown == 0) {
        Bee *bee = place->randomBee();
        if (bee != nullptr) {
            chewCountDown = chewDuration;
            bee->kill();
        }
    } else {
        chewCountDown--;
    }
}