#include "WallAnt.h"

/**
 * @brief 构造一个新的 WallAnt
 *
 * 默认 WallAnt 的属性：
 *
 * - 类名 name 为 "Wall"
 *
 * - 食物消耗 foodCost 为 4
 *
 * @param health WallAnt 的初始生命值，默认为 4.0
 */
WallAnt::WallAnt(double health)
    : Ant(health, {
                      .name = "WallAnt",
                      .foodCost = 4,
                  }) {}