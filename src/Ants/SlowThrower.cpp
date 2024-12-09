#include "SlowThrower.h"
#include "Bee.h"

/**
 * @brief 构造一个新的 SlowThrower
 *
 * 默认 SlowThrower 的属性：
 *
 * - 类名 name 为 "Slow"
 *
 * - 食物消耗 foodCost 为 4
 *
 * @param health SlowThrower 的初始生命值，默认为 1.0
 */
SlowThrower::SlowThrower(double health)
    : ThrowerAnt(health, {
                             .name = "SlowThrower",
                             .foodCost = 4,
                         }) {}

/**
 * @brief 对目标 Bee 进行远程攻击
 *
 * 对指定的 Bee 进行远程攻击，使其减速 3 回合。
 *
 * @param target 目标 Bee
 */
void SlowThrower::throwAt(Bee *target) {
    if (target != nullptr) {
        target->slow(3);
    }
}