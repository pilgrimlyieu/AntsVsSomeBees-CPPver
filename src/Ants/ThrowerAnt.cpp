#include "ThrowerAnt.hpp"
#include "Bee.hpp"
#include "GameState.hpp"
#include "Place.hpp"
#include "WebSocket.hpp"

/**
 * @brief 获取 ThrowerAnt 射程范围内最近的 Bee
 *
 * 从当前位置向入口，直到 Hive 方向遍历，获取射程范围内最近的 Bee 。
 *
 * 若有多只 Bee 与 ThrowerAnt 的距离相同，则随机选择一只 Bee 。
 *
 * 没有找到 Bee 时，则返回 `nullptr`。
 *
 * @return 射程范围内最近的 Bee
 */
Bee *ThrowerAnt::nearestBee() {
    Place *place = this->place;
    int distance = 0;
    while (!place->getIsHive()) {
        if (place->bees.size() > 0 && distance >= minRange && distance <= maxRange) {
            return place->randomBee();
        }
        distance++;
        place = place->entrance;
    }
    return nullptr;
}

/**
 * @brief 对目标 Bee 进行远程攻击
 *
 * 对指定的 Bee 进行远程攻击，对其造成伤害。
 *
 * @param target 目标 Bee
 */
void ThrowerAnt::throwAt(Bee *target) {
    WebSocket::onThrowerAttack(this, target);
    if (target != nullptr) {
        log(LOGINFO, format("{} throws at {}, causing {} damage", *this, *target, getDamage()));
        target->reduceHealth(getDamage());
    } else {
        log(LOGINFO, format("{} throws at nothing", *this));
    }
}

/**
 * @brief 执行 ThrowerAnt 的动作
 *
 * ThrowerAnt 的动作是对射程范围内最近的 Bee 进行远程攻击。
 */
void ThrowerAnt::action(GameState &gamestate) {
    throwAt(nearestBee());
}