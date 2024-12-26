#include "Ant.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief Ant 类的构造函数，初始化一个 Ant
 *
 * 默认 Ant 的属性：
 *
 * - 类名 name 为 "Ant"
 *
 * - 食物消耗 foodCost 为 0
 *
 * - 是否被加成 buffed 为 false
 *
 * - 是否可以容纳其他 Ant isContainer 为 false
 *
 * - 是否阻挡路径 blocksPath 为 true
 *
 * @param health Ant 的初始生命值，默认为 1.0
 * @param properties Ant 的属性
 */
Ant::Ant(double health, ant_properties properties)
    : Insect(health, nullptr, properties), buffed(properties.buffed), foodCost(properties.foodCost),
      isContainer(properties.isContainer), blocksPath(properties.blocksPath) {}

/**
 * @brief 执行 Ant 的动作
 *
 * 这个函数定义了 Ant 在给定 GameState 下的具体行为。
 *
 * @param gamestate 当前的游戏状态。
 */
void Ant::action(GameState &gamestate) {
    // TODO
}

/**
 * @brief 受伤回调函数
 *
 * 当 Ant 受伤时调用此函数。
 */
void Ant::injuryCallback() {
    // TODO
}

/**
 * @brief 死亡回调函数
 *
 * 当 Ant 死亡时调用此函数。
 */
void Ant::deathCallback() {
    // TODO
}

/**
 * @brief 判断当前 Ant 是否可以容纳另一个 Ant
 *
 * 默认 Ant 始终不能容纳其他 Ant 。
 *
 * @param other 指向另一个 Ant 的指针。
 * @return 若当前 Ant 可以容纳 other，则返回 true；否则返回 false。
 */
bool Ant::canContain(Ant *other) {
    return false;
}

/**
 * @brief 容纳另一个 Ant
 *
 * 默认 Ant 不能容纳其他 Ant ，因此调用此函数会抛出异常。
 *
 * @param other 指向要容纳的另一只 Ant 的指针。
 * @throws invalid_argument 当不能容纳另一只 Ant 时抛出异常。
 */
void Ant::storeAnt(Ant *other) {
    THROW_EXCEPTION(invalid_argument, format("{} cannot contain {}", *this, *other));
}

/**
 * @brief 从当前 Ant 中移除另一个 Ant
 *
 * 默认 Ant 不能容纳其他 Ant ，因此调用此函数会抛出异常。
 *
 * @param other 指向要移除的 Ant 的指针。
 * @throws invalid_argument 当不能容纳另一只 Ant 时抛出异常。
 */
void Ant::removeAnt(Ant *other) {
    THROW_EXCEPTION(invalid_argument, format("{} cannot contain {}", *this, *other));
}

/**
 * @brief 将当前 Ant 添加到指定的 Place 中
 *
 * 若 Place 中没有 Ant ，则将当前 Ant 添加到 Place 中。
 *
 * 若 Place 中已经有 Ant ，则按照以下顺序处理：
 *
 * 1. 若 Place 中的 Ant 可以容纳当前 Ant ，则当前 Ant 由其容纳；
 *
 * 2. 若当前 Ant 可以容纳 Place 中的 Ant ，则 Place 中的 Ant 由当前 Ant 容纳；
 *
 * 3. 否则，抛出异常。
 *
 * @param place 指向要添加到的 Place 的指针。
 * @throws invalid_argument 若当前 Ant 不能容纳 Place 中的 Ant 。
 */
void Ant::addTo(Place *place) {
    if (place->ant == nullptr) {
        place->ant = this;
        log(LOGINFO, format("{} is added to {}", *this, *place));
    } else {
        if (place->ant->canContain(this)) {
            place->ant->storeAnt(this);
        } else if (canContain(place->ant)) {
            storeAnt(place->ant);
            place->ant = this;
        } else {
            THROW_EXCEPTION(invalid_argument, format("Two ants in {}", *place));
        }
    }
    Insect::addTo(place);
}

/**
 * @brief 从指定的 Place 中移除当前 Ant
 *
 * 若当前 Ant 在 Place 中，则将其从 Place 中移除。
 *
 * 若当前 Ant 不在 Place 中，则抛出异常。
 *
 * @param place 指向要移除的 Place 的指针。
 * @throws invalid_argument 若当前 Ant 不在 Place 中。
 */
void Ant::removeFrom(Place *place) {
    if (place->ant == this) {
        place->ant = nullptr;
        log(LOGINFO, format("{} is removed from {}", *this, *place));
    } else if (place->ant == nullptr) {
        THROW_EXCEPTION(invalid_argument, format("{} is not in {}", *this, *place));
    } else {
        removeAnt(place->ant);
    }
    Insect::removeFrom(place);
}

/**
 * @brief 为当前 Ant 加成
 *
 * 若当前 Ant 尚未被加成，则将其攻击力翻倍。
 */
void Ant::buff() {
    if (!buffed) {
        damage *= 2;
        buffed = true;
        log(LOGINFO, format("{} is buffed", *this));
    }
}