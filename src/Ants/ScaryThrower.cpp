#include "ScaryThrower.h"
#include "Bee.h"

/**
 * @brief 构造一个新的 ScaryThrower
 *
 * 默认 ScaryThrower 的属性：
 *
 * - 类名 name 为 "Scary"
 *
 * - 食物消耗 foodCost 为 6
 *
 * @param health ScaryThrower 的初始生命值，默认为 1
 */
ScaryThrower::ScaryThrower(double health)
    : ThrowerAnt(health, {
                             .name = "ScaryThrower",
                             .foodCost = 6,
                         }) {}

/**
 * @brief 对目标 Bee 进行远程攻击
 *
 * 对指定的 Bee 进行远程攻击，使其受到恐惧效果 2 回合。
 *
 * @param target 目标 Bee
 */
void ScaryThrower::throwAt(Bee *target) {
    if (target != nullptr) {
        target->scare(2);
        log(LOGINFO, format("{} scares {} for 2 rounds", (string) * this, (string)*target));
    } else {
        log(LOGINFO, format("{} throws at nothing", (string) * this));
    }
}