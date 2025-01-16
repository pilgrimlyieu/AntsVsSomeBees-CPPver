#include "HarvestAnt.hpp"
#include "GameState.hpp"

/**
 * @brief 执行 HarvestAnt 的动作
 *
 * HarvestAnt 的动作是收获食物，每次收获 1 个食物。
 *
 * @param gamestate 当前的游戏状态。
 */
void HarvestAnt::action(GameState &gamestate) {
    gamestate.food += 1;
    log(LOGINFO, format("{} harvests 1 food", *this));
    log(LOGTEST, format("Food: {}", gamestate.food));
}