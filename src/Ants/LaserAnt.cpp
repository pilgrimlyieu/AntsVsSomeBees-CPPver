#include "LaserAnt.h"
#include "Bee.h"
#include "Place.h"

/**
 * @brief 获取 LaserAnt 的所有攻击目标及其距离
 *
 * 从当前位置向入口，直到 Hive 方向遍历，获取所有攻击目标及其距离。
 *
 * @return 所有攻击目标及其距离
 */
std::unordered_map<Insect *, int> LaserAnt::getTargets() {
    std::unordered_map<Insect *, int> targets;
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
int LaserAnt::getDamage(int distance) {
    double trueDamage = damage - 0.25 * distance - ((double)insectsShot) / 16;
    return (int)std::max(0.0, trueDamage);
}

/**
 * @brief 执行 LaserAnt 的动作
 *
 * LaserAnt 的动作是对所有攻击目标射击。
 *
 * 对于每个目标，计算 LaserAnt 对其造成的伤害，并减少目标的生命值。
 */
void LaserAnt::action(GameState &gamestate) {
    std::unordered_map<Insect *, int> targets = getTargets();
    for (auto &target : targets) {
        int damage = getDamage(target.second);
        target.first->reduceHealth(damage);
        if (damage > 0) {
            insectsShot++;
        }
    }
}