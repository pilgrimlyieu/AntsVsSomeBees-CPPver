#include "Insect.h"
#include "Place.h"

/**
 * @brief Constructs a new Insect object with the specified health and place.
 *
 * @param health The initial health of the insect.
 * @param place A pointer to the Place object where the insect is located.
 */
Insect::Insect(int health, Place *place) {
    this->health = health;
    this->place = place;
}

/**
 * @brief Reduces the health of the insect by a specified amount.
 *
 * This function decreases the health of the insect by the given amount.
 * If the health drops to zero or below, it triggers the death callback
 * and removes the insect from its current place.
 *
 * @param amount The amount by which to reduce the insect's health.
 */
void Insect::reduceHealth(int amount) {
    health -= amount;
    injuryCallback();
    if (health <= 0) {
        deathCallback();
        place->removeInsect(this);
        delete this;
    }
}

/**
 * @brief Handles the action of the insect.
 *
 * This function is called to perform an action for the insect within the given game state.
 * The specific action performed by the insect is defined by the derived class.
 */
void Insect::injuryCallback() {
    // TODO
}

/**
 * @brief Handles the death of the insect.
 */
void Insect::deathCallback() {
    // TODO
}

/**
 * @brief Adds the insect to a specified place.
 *
 * This function sets the place of the insect to the given place.
 *
 * @param place A pointer to the Place object where the insect will be added.
 */
void Insect::addTo(Place *place) {
    this->place = place;
}

/**
 * @brief Removes the insect from the specified place and deletes the insect object.
 *
 * This function sets the place pointer of the insect to nullptr.
 *
 * @param place A pointer to the Place object from which the insect is being removed.
 */
void Insect::removeFrom(Place *place) {}

/**
 * @brief Converts the Insect object to a string representation.
 *
 * This operator overload allows an Insect object to be converted to a
 * string that includes the name, health, and damage of the insect.
 *
 * @return A string representation of the Insect object in the format
 *         "name(health, damage)".
 */
Insect::operator string() const {
    return format("%s(%d, %d)", name.c_str(), health, damage);
}

/**
 * @brief Kills the insect by reducing its health to zero.
 */
void Insect::kill() {
    reduceHealth(health);
}