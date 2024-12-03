#include "ScaryThrower.h"
#include "Bee.h"

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
    }
}