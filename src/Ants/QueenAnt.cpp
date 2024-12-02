#include "QueenAnt.h"
#include "ContainerAnt.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Constructs a QueenAnt if one does not already exist in the game state.
 *
 * This function checks if the QueenAnt is already present in the game state.
 *
 * If not, it constructs a new QueenAnt and assigns it to the game state's Queen pointer.
 *
 * @param gamestate Reference to the current game state.
 * @return Pointer to the newly constructed QueenAnt if one did not already exist, otherwise
 * nullptr.
 */
QueenAnt *QueenAnt::construct(GameState &gamestate) {
    if (gamestate.Queen == nullptr) {
        gamestate.Queen = (QueenAnt *)Ant::construct(gamestate);
        return gamestate.Queen;
    }
    return nullptr;
}

/**
 * @brief Executes the action of the QueenAnt.
 *
 * The QueenAnt buffs all the ants after it in the path.
 *
 * @param gamestate The current state of the game.
 */
void QueenAnt::action(GameState &gamestate) {
    ThrowerAnt::action(gamestate);
    Place *currentPlace = place->exit;
    while (currentPlace != nullptr) {
        Ant *ant = currentPlace->ant;
        if (ant != nullptr) {
            ant->buff();
            if (ant->isContainer && ((ContainerAnt *)ant)->antContained != nullptr) {
                ((ContainerAnt *)ant)->antContained->buff();
            }
        }
        currentPlace = currentPlace->exit;
    }
}

/**
 * @brief Reduces the health of the QueenAnt by a specified amount.
 *
 * This function decreases the health of the QueenAnt by the given amount.
 * If the health drops to zero or below, it indicates that the QueenAnt has died,
 * and the game should end.
 *
 * @param amount The amount by which to reduce the QueenAnt's health.
 */
void QueenAnt::reduceHealth(int amount) {
    health -= amount;
    if (health <= 0) {
        // TODO: Game ends when QueenAnt dies
    }
}

/**
 * @brief This method is intentionally left empty because the game ends when the QueenAnt dies.
 *
 * @param place The place from which the QueenAnt would be removed. This parameter is not used.
 */
void QueenAnt::removeFrom(Place *place) {
    // Do nothing because game ends when QueenAnt dies
}