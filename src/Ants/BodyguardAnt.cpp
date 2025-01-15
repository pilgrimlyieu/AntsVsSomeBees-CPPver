#include "BodyguardAnt.hpp"

/**
 * @brief 构造一个新的 BodyguardAnt
 *
 * 默认 BodyguardAnt 的属性：
 *
 * - 类名 name 为 "Bodyguard"
 *
 * - 食物消耗 foodCost 为 4
 *
 * @param health BodyguardAnt 的初始生命值，默认为 2.0
 */
BodyguardAnt::BodyguardAnt(double health)
    : ContainerAnt(health, {
                               {
                                .foodCost = 4,
                                },
                               .name = "BodyguardAnt",
}) {}