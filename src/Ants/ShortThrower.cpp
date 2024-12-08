#include "ShortThrower.h"

/**
 * @brief 构造一个新的 ShortThrower
 *
 * 默认 ShortThrower 的属性：
 *
 * - 类名 name 为 "ShortThrower"
 *
 * - 食物消耗 foodCost 为 2
 *
 * - 最大射程 maxRange 为 3
 *
 * @param health ShortThrower 的初始生命值，默认为 1.0
 */
ShortThrower::ShortThrower(double health)
    : ThrowerAnt(health, {
                             .name = "ShortThrower",
                             .foodCost = 2,
                             .maxRange = 3,
                         }) {}
