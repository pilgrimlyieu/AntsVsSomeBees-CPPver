#include "ScaryThrower.hpp"
#include "Bee.hpp"

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
        log(LOGINFO, format("{} scares {} for 2 rounds", this, target));
    } else {
        log(LOGTEST, format("{} throws at nothing", this));
    }
}