#include "SlowThrower.h"
#include "Bee.h"

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