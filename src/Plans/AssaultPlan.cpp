#include "AssaultPlan.h"

/**
 * @brief 添加一波 Bee 的攻击
 *
 * @param beeType 要添加的 Bee 类型
 * @param beeHealth 要添加的 Bee 的生命值
 * @param time 要添加的 Bee 的时间
 * @param count 要添加的 Bee 的数量
 * @return 返回 AssaultPlan 的引用
 */
AssaultPlan &AssaultPlan::addWave(bee_t beeType, double beeHealth, g_time time, int count) {
    bee_list bees;
    for (int i = 0; i < count; i++) {
        bees.push_back(beeType(beeHealth));
    }
    if (waves.find(time) == waves.end()) {
        waves[time] = bees;
    } else {
        waves[time].insert(waves[time].end(), bees.begin(), bees.end());
    }
    return *this;
}

/**
 * @brief 获取所有 Bee
 *
 * @return 所有 Bee 的列表
 */
bee_list AssaultPlan::getBees() const {
    bee_list bees;
    for (auto &wave : waves) {
        bees.insert(bees.end(), wave.second.begin(), wave.second.end());
    }
    return bees;
}