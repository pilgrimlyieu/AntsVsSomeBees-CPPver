#include "HarvestAnt.h"
#include "GameState.h"

/**
 * @brief Increases the food count in the game state.
 *
 * This function represents the action of a HarvestAnt, which
 * increases the food count in the provided game state by 1.
 *
 * @param gamestate A reference to the current game state.
 */
void HarvestAnt::action(GameState &gamestate) {
    gamestate.food += 1;
}