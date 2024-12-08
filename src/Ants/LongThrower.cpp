#include "LongThrower.h"

/**
 * @brief 构造一个新的 LongThrower
 *
 * 默认 LongThrower 的属性：
 *
 * - 类名 name 为 "LongThrower"
 *
 * - 食物消耗 foodCost 为 2
 *
 * - 最小射程 minRange 为 5
 *
 * @param health LongThrower 的初始生命值，默认为 1.0
 */
LongThrower::LongThrower(double health)
    : ThrowerAnt(health, {
                             .name = "LongThrower",
                             .damage = 1.0,
                             .foodCost = 2,
                             .minRange = 5,
                         }) {}