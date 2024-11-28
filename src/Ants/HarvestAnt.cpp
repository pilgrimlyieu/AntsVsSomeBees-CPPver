#include "HarvestAnt.h"
#include "GameState.h"

void HarvestAnt::action(GameState &gamestate) {
    gamestate.food += 1;
}