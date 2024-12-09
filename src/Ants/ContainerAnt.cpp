#include "ContainerAnt.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief 构造一个新的 ContainerAnt
 *
 * 默认 ContainerAnt 的属性：
 *
 * - 类名 name 为 "Container"
 *
 * - 是否可以容纳其他 Ant isContainer 为 true
 *
 * - 容纳的 Ant antContained 为 nullptr
 *
 * @param health ContainerAnt 的初始生命值，默认为 1.0
 */
ContainerAnt::ContainerAnt(double health, container_ant_properties properties)
    : Ant(health, properties), antContained(nullptr) {}

/**
 * @brief 判断当前 ContainerAnt 是否还可以容纳另一个 Ant
 *
 * 默认情况下 ContainerAnt 只能容纳一个 Ant ，同时不允许容纳其他 ContainerAnt 。
 *
 * @param other 要容纳的 Ant
 * @return 当前 ContainerAnt 是否还可以容纳另一个 Ant
 */
bool ContainerAnt::canContain(Ant *other) {
    return antContained == nullptr && !other->isContainer;
}

/**
 * @brief 将指定的 Ant 容纳到当前 ContainerAnt 中
 *
 * @param ant 要容纳的 Ant
 */
void ContainerAnt::storeAnt(Ant *ant) {
    antContained = ant;
}

/**
 * @brief 从当前 ContainerAnt 中移除指定的 Ant
 *
 * @param ant 要移除的 Ant
 * @throws std::invalid_argument 若当前 ContainerAnt 并未容纳指定的 Ant
 */
void ContainerAnt::removeAnt(Ant *ant) {
    if (antContained != ant) {
        THROW_EXCEPTION(
            std::invalid_argument,
            std::format("{} does not contain {}", (std::string) * this, (std::string)*ant));
    }
    antContained = nullptr;
}

/**
 * @brief 从指定的 Place 中移除当前 ContainerAnt
 *
 * 若当前 ContainerAnt 在 Place 中，则将其从 Place 中移除，并把容纳的 Ant 添加到 Place 中。
 *
 * @param place 指向要移除的 Place 的指针
 */
void ContainerAnt::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = antContained;
        Insect::removeFrom(place);
    } else {
        Ant::removeFrom(place);
    }
}

/**
 * @brief ContainerAnt 的行动函数
 *
 * 若当前 ContainerAnt 中包含 Ant ，则执行该 Ant 的行动函数。
 *
 * @param gamestate 游戏状态
 */
void ContainerAnt::action(GameState &gamestate) {
    if (antContained != nullptr) {
        antContained->action(gamestate);
    }
}