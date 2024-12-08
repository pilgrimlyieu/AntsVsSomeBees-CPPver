#include "HarvestAnt.h"
#include "GameState.h"

/**
 * @brief 构造一个新的 HarvestAnt
 *
 * 默认 HarvestAnt 的属性：
 *
 * - 类名 name 为 "Harvester"
 *
 * - 食物消耗 foodCost 为 2
 *
 * @param health HarvestAnt 的初始生命值，默认为 1.0
 */
HarvestAnt::HarvestAnt(double health)
    : Ant(health, {
                      .name = "Harvester",
                      .foodCost = 2,
                  }) {}

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