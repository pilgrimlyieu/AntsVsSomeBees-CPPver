#include "SlowThrower.hpp"
#include "Bee.hpp"

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
        log(LOGINFO, format("{} slows {} for 3 rounds", *this, *target));
    } else {
        log(LOGTEST, format("{} throws at nothing", *this));
    }
}