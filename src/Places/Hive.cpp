#include "Hive.hpp"
#include "Bee.hpp"
#include "GameState.hpp"

/**
 * @brief 构造一个新的 Hive
 *
 * 默认 Hive 的属性：
 *
 * - 是否是 Hive isHive 为 true
 *
 * 初始化 Hive 的名称为 "Hive"，且不包含任何 Ant 。
 */
Hive::Hive(AssaultPlan aP) : Place("Hive", nullptr), assaultPlan(std::move(aP)) {
    bees.clear();
    for (auto bee : assaultPlan.getBees()) {
        addInsect(bee);
    }
    // Always `nullptr` for a Hive
    this->entrance = nullptr;
    this->ant = nullptr;
}

void Hive::strategy(GameState &gameState) {
    places_list exits;
    for (auto &[name, place] : gameState.places) {
        if (place->entrance == this) {
            exits.push_back(place);
        }
    }
    for (auto bee : assaultPlan[gameState.time]) {
        gameState.activeBees.push_back(bee);
        log(LOGTEST, format("Bee {} added", string(*bee)));
        bee->moveTo(randomElement(exits));
    }
}