#include "HarvestAnt.h"
#include "GameState.h"

/**
 * @brief 执行 HarvestAnt 的动作
 *
 * HarvestAnt 的动作是收获食物，每次收获 1 个食物。
 *
 * @param gamestate 当前的游戏状态。
 */
void HarvestAnt::action(GameState &gamestate) {
    gamestate.food += 1;
}