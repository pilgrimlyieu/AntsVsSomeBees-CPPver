#include "LaserAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief 构造一个新的 LaserAnt
 *
 * 默认 LaserAnt 的属性：
 *
 * - 类名 name 为 "Laser"
 *
 * - 食物消耗 foodCost 为 10
 *
 * - 伤害 damage 为 2.0
 *
 * - 射击的昆虫数量 insectsShot 为 0
 *
 * @param health LaserAnt 的初始生命值，默认为 1.0
 */
LaserAnt::LaserAnt(double health)
    : ThrowerAnt(health,
                 {
                     .name = "LaserAnt",
                     .damage = 2.0,
                     .foodCost = 10,
                 }),
      insectsShot(0) {}

/**
 * @brief 获取 LaserAnt 的所有攻击目标及其距离
 *
 * 从当前位置向入口，直到 Hive 方向遍历，获取所有攻击目标及其距离。
 *
 * @return 所有攻击目标及其距离
 */
unordered_map<Insect *, int> LaserAnt::getTargets() {
    unordered_map<Insect *, int> targets;
    int distance = 0;
    Place *currentPlace = place;
    while (!currentPlace->isHive) {
        if (currentPlace->ant != nullptr && currentPlace->ant != this) {
            targets[currentPlace->ant] = distance;
        }
        for (Bee *bee : currentPlace->bees) {
            targets[bee] = distance;
        }
        currentPlace = currentPlace->entrance;
        distance++;
    }
    return targets;
}

/**
 * @brief 获取 LaserAnt 对指定距离的目标造成的伤害
 *
 * 最终伤害 = 基础伤害 - 0.25 * 距离 - 已射击昆虫数量 / 16
 *
 * @param distance 目标距离
 * @return 造成的伤害
 */
double LaserAnt::getDamage(int distance) {
    double trueDamage = damage - 0.25 * distance - ((double)insectsShot) / 16;
    return std::max(0.0, trueDamage);
}

/**
 * @brief 执行 LaserAnt 的动作
 *
 * LaserAnt 的动作是对所有攻击目标射击。
 *
 * 对于每个目标，计算 LaserAnt 对其造成的伤害，并减少目标的生命值。
 */
void LaserAnt::action(GameState &gamestate) {
    unordered_map<Insect *, int> targets = getTargets();
    for (auto &target : targets) {
        double damage = getDamage(target.second);
        target.first->reduceHealth(damage);
        if (damage > 0) {
            insectsShot++;
        }
    }
}