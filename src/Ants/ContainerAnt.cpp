#include "ContainerAnt.hpp"
#include "GameState.hpp"
#include "Place.hpp"

/**
 * @brief 判断当前 ContainerAnt 是否还可以容纳另一个 Ant
 *
 * 默认情况下 ContainerAnt 只能容纳一个 Ant ，同时不允许容纳其他 ContainerAnt 。
 *
 * @param other 要容纳的 Ant
 * @return 当前 ContainerAnt 是否还可以容纳另一个 Ant
 */
bool ContainerAnt::canContain(Ant *other) {
    return antContained == nullptr && dynamic_cast<ContainerAnt *>(other) == nullptr;
}

/**
 * @brief 将指定的 Ant 容纳到当前 ContainerAnt 中
 *
 * @param ant 要容纳的 Ant
 */
void ContainerAnt::storeAnt(Ant *ant) {
    antContained = ant;
    log(LOGINFO, format("{} is stored in {}", *ant, *this));
}

/**
 * @brief 从当前 ContainerAnt 中移除指定的 Ant
 *
 * @param ant 要移除的 Ant
 * @throws invalid_argument 若当前 ContainerAnt 并未容纳指定的 Ant
 */
void ContainerAnt::removeAnt(Ant *ant) {
    if (antContained != ant) {
        THROW_EXCEPTION(invalid_argument, format("{} does not contain {}", *this, *ant));
    }
    antContained = nullptr;
    log(LOGTEST, format("{} is removed from {}", *ant, *this));
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

/**
 * @brief 序列化当前 ContainerAnt
 *
 * @return 当前 ContainerAnt 的序列化结果
 */
json ContainerAnt::serialize() const {
    json j = Ant::serialize();
    j["antContained"] = (antContained != nullptr) ? antContained->serialize() : nullptr;
    return j;
}