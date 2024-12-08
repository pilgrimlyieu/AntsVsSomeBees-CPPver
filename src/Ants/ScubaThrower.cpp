#include "ScubaThrower.h"

/**
 * @brief 构造一个新的 ScubaThrower
 *
 * 默认 ScubaThrower 的属性：
 *
 * - 类名 name 为 "Scuba"
 *
 * - 食物消耗 foodCost 为 6
 *
 * - 是否抗水 isWaterProof 为 true
 *
 * @param health ScubaThrower 的初始生命值，默认为 1
 */
ScubaThrower::ScubaThrower(double health, scuba_thrower_properties properties)
    : ThrowerAnt(health, properties) {}