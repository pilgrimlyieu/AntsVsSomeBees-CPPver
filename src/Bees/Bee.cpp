#include "Bee.h"
#include "Ant.h"
#include "Place.h"

/**
 * @brief Constructs a new Bee object with the specified health and place.
 *
 * @param health The initial health of the bee.
 * @param place A pointer to the Place object where the bee is located.
 */
Bee::Bee(int health, Place *place) : Insect(health, place) {}

/**
 * @brief Causes the bee to sting an ant, reducing the ant's health.
 *
 * @param ant A pointer to the Ant object that will be stung.
 */
void Bee::sting(Ant *ant) {
    ant->reduceHealth(damage);
}

/**
 * @brief Moves the bee to a new place.
 *
 * This function removes the bee from its current place and adds it to the specified new place.
 *
 * @param place A pointer to the new Place object where the bee will be moved.
 */
void Bee::moveTo(Place *place) {
    this->place->removeInsect(this);
    place->addInsect(this);
}

/**
 * @brief Checks if the bee is blocked by an ant.
 *
 * This function determines if the bee's path is blocked by an ant in its current place.
 * It returns true if there is an ant in the bee's place and the ant blocks the path.
 *
 * @return true if the bee is blocked by an ant, false otherwise.
 */
bool Bee::blocked() {
    return place->ant != nullptr && place->ant->blocksPath;
}

/**
 * @brief Perform an action for the Bee.
 *
 * This method is called to perform an action for the Bee within the given game state.
 *
 * @param gamestate The current state of the game.
 */
void Bee::action(GameState &gamestate) {
    // TODO
}

/**
 * @brief Handles the injury of the Bee object.
 */
void Bee::injuryCallback() {
    // TODO
}

/**
 * @brief Handles the death of the Bee object.
 */
void Bee::deathCallback() {
    // TODO
}

/**
 * @brief Adds the current Bee instance to the specified Place.
 *
 * This function adds the current Bee instance to the bees vector of the given Place.
 * It also calls the addTo function of the base class Insect to perform any additional
 * operations required by the base class.
 *
 * @param place A pointer to the Place where the Bee should be added.
 */
void Bee::addTo(Place *place) {
    place->bees.push_back(this);
    Insect::addTo(place);
}

/**
 * @brief Removes the bee from the specified place.
 *
 * This function removes the bee from the list of bees in the given place
 * and then calls the base class's removeFrom function to perform any
 * additional removal operations.
 *
 * @param place A pointer to the Place object from which the bee should be removed.
 */
void Bee::removeFrom(Place *place) {
    place->bees.remove(this);
    Insect::removeFrom(place);
}

/**
 * @brief Slows down the bee for a specified length of time.
 *
 * @param length The duration for which the bee will be slowed down.
 */
void Bee::slow(g_time length) {
    slowedTime += length;
}

/**
 * @brief Scares the bee for a specified length of time.
 *
 * This function sets the bee's scared state to true and increases the scared time
 * by the specified length if the bee is not already scared.
 *
 * @param length The duration for which the bee should be scared.
 */
void Bee::scare(g_time length) {
    if (!isScared) {
        scaredTime += length;
        isScared = true;
    }
}
