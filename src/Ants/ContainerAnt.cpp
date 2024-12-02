#include "ContainerAnt.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Constructs a new ContainerAnt object with the specified health.
 *
 * This constructor initializes a ContainerAnt object with the given health value.
 *
 * It also sets the antContained member to nullptr.
 *
 * @param health The initial health value for the ContainerAnt. Default value is 1.
 */
ContainerAnt::ContainerAnt(int health) : Ant(health), antContained(nullptr) {}

/**
 * @brief Determines if the current ContainerAnt can contain another Ant.
 *
 * This function checks if the current ContainerAnt is not already containing another Ant
 * and if the other Ant is not a container itself.
 *
 * @param other A pointer to the Ant that is being checked for containment.
 * @return true if the current ContainerAnt can contain the other Ant, false otherwise.
 */
bool ContainerAnt::canContain(Ant *other) {
    return antContained == nullptr && !other->isContainer;
}

/**
 * @brief Stores the given ant in the container.
 *
 * This function assigns the provided Ant pointer to the antContained member variable,
 * effectively storing the ant within the ContainerAnt object.
 *
 * @param ant A pointer to the Ant object to be stored.
 */
void ContainerAnt::storeAnt(Ant *ant) {
    antContained = ant;
}

/**
 * @brief Removes the specified ant from the container.
 *
 * This function checks if the specified ant is the one currently stored in the container.
 *
 * If it is, the antContained member variable is set to nullptr, effectively removing the ant.
 *
 * If the specified ant is not the one stored in the container, an exception is thrown.
 *
 * @param ant Pointer to the Ant object to be removed.
 * @throws std::invalid_argument if the container does not contain the specified ant.
 */
void ContainerAnt::removeAnt(Ant *ant) {
    if (antContained != ant) {
        throw invalid_argument(
            format("%s does not contain %s", string(*this).c_str(), string(*ant).c_str()));
    }
    antContained = nullptr;
}

/**
 * @brief Removes the ContainerAnt from the specified place.
 *
 * This function checks if the current ContainerAnt is the ant present in the given place.
 *
 * If it is, it sets the place's ant to the ant contained within the ContainerAnt.
 *
 * Otherwise, it calls the removeFrom function of the base Ant class.
 *
 * @param place A pointer to the Place object from which the ContainerAnt should be removed.
 */
void ContainerAnt::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = antContained;
        Insect::removeFrom(place);
    } else {
        Ant::removeFrom(place);
    }
}

/**
 * @brief Executes the action of the contained ant if it exists.
 *
 * This method checks if there is an ant contained within the ContainerAnt.
 *
 * If there is, it calls the action method of the contained ant, passing the
 * current game state as a parameter.
 *
 * @param gamestate The current state of the game.
 */
void ContainerAnt::action(GameState &gamestate) {
    if (antContained != nullptr) {
        antContained->action(gamestate);
    }
}