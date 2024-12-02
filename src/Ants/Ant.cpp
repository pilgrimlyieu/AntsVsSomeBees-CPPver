#include "Ant.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Constructs a new Ant object with the specified health.
 *
 * @param health The initial health of the Ant. Default value is 1.
 */
Ant::Ant(int health) : Insect(health, nullptr), buffed(false) {}

/**
 * @brief a new Ant object if there is enough food in the GameState.
 *
 * @param gamestate Reference to the current game state.
 * @return A pointer to a new Ant object if there is enough food, otherwise nullptr.
 */
Ant *Ant::construct(GameState &gamestate) {
    if (foodCost > gamestate.food) {
        return nullptr;
    }
    return new Ant();
}

/**
 * @brief Perform an action for the Ant.
 *
 * This method is called to perform an action for the Ant within the given game state.
 *
 * The specific action performed by the Ant is defined by the derived class.
 *
 * @param gamestate The current state of the game.
 */
void Ant::action(GameState &gamestate) {
    // TODO
}

/**
 * @brief Handles the injury of the Ant object.
 */
void Ant::injuryCallback() {
    // TODO
}

/**
 * @brief Handles the death of the Ant object.
 */
void Ant::deathCallback() {
    // TODO
}

/**
 * @brief Determines if the current Ant object can contain another Ant object.
 *
 * The default implementation always returns false.
 *
 * @param other A pointer to another Ant object to check containment.
 * @return true if the current Ant object can contain the other Ant object, false otherwise.
 */
bool Ant::canContain(Ant *other) {
    return false;
}

/**
 * @brief Throws an exception indicating that an Ant cannot store another Ant.
 *
 * @param other Pointer to another Ant object.
 * @throws std::invalid_argument Always throws this exception with the message "Ant cannot store
 * another ant".
 */
void Ant::storeAnt(Ant *other) {
    throw invalid_argument("Ant cannot store another ant");
}

/**
 * @brief Removes the specified Ant from this Ant if it is contained.
 *
 * @param other A pointer to the Ant object to be removed.
 */
void Ant::removeAnt(Ant *other) {}

/**
 * @brief Adds the current Ant to the specified place.
 *
 * This method attempts to add the current Ant to the given place.
 *
 * If the place already has an Ant, it checks if the existing Ant can contain the current Ant or
 * vice versa.
 *
 * If neither can contain the other and the place already has an Ant, an exception is thrown.
 *
 * @param place A pointer to the Place object where the Ant should be added.
 *
 * @throws std::invalid_argument if there are two Ants in the same place and neither can contain the
 * other.
 */
void Ant::addTo(Place *place) {
    if (place->ant == nullptr) {
        place->ant = this;
    } else {
        if (place->ant->canContain(this)) {
            place->ant->storeAnt(this);
        } else if (canContain(place->ant)) {
            storeAnt(place->ant);
            place->ant = this;
        } else if (place->ant->place != nullptr) {
            throw invalid_argument(format("Two ants in one place: %s", place->name.c_str()));
        }
    }
    Insect::addTo(place);
}

/**
 * @brief Removes the Ant from the specified place.
 *
 * This function checks if the Ant is currently at the given place.
 *
 * If it is, the Ant is removed by setting the place's Ant pointer to nullptr.
 *
 * If the place's Ant pointer is already nullptr, an invalid_argument exception is
 * thrown indicating that the Ant is not in the specified place.
 *
 * If the place has a different Ant, that Ant is removed using the removeAnt function.
 *
 * @param place A pointer to the Place object from which the Ant should be removed.
 * @throws std::invalid_argument if the Ant is not in the specified place.
 */
void Ant::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = nullptr;
    } else if (place->ant == nullptr) {
        throw invalid_argument(format("Ant is not in %s", place->name.c_str()));
        // TODO: Add `str` method
    } else {
        removeAnt(place->ant);
    }
    Insect::removeFrom(place);
}

/**
 * @brief Doubles the damage of the Ant if it is not already buffed.
 *
 * This method checks if the Ant is already buffed.
 *
 * If not, it doubles the damage of the Ant and sets the buffed flag to true to indicate that the
 * Ant has been buffed.
 */
void Ant::buff() {
    if (!buffed) {
        damage *= 2;
        buffed = true;
    }
}