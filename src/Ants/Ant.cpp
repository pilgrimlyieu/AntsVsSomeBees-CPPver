#include "Ant.hpp"
#include "GameState.hpp"
#include "Place.hpp"

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
        buffed = true;
        log(LOGINFO, format("{} is buffed", *this));
    }
}