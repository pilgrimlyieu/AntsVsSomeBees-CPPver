#include "ThrowerAnt.h"
#include "Bee.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief 构造一个新的 ThrowerAnt
 *
 * 默认 ThrowerAnt 的属性：
 *
 * - 类名 name 为 "Thrower"
 *
 * - 伤害 damage 为 1.0
 *
 * - 食物消耗 foodCost 为 3
 *
 * - 最小射程 minRange 为 0
 *
 * - 最大射程 maxRange 为 INT_MAX
 *
 * @param health ThrowerAnt 的初始生命值，默认为 1.0
 * @param properties ThrowerAnt 的属性
 */
ThrowerAnt::ThrowerAnt(double health, thrower_ant_properties properties)
    : Ant(health, properties), minRange(properties.minRange), maxRange(properties.maxRange) {}

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
    while (!place->isHive) {
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
    if (target != nullptr) {
        target->reduceHealth(damage);
        log(LOGINFO,
            format("{} throws at {}, causing {} damage", string(*this), string(*target), damage));
    } else {
        log(LOGINFO, format("{} throws at nothing", string(*this)));
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