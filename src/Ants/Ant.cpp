#include "BodyguardAnt.hpp"
#include "ContainerAnt.hpp"
#include "FireAnt.hpp"
#include "GameState.hpp"
#include "HarvestAnt.hpp"
#include "HungryAnt.hpp"
#include "LaserAnt.hpp"
#include "LongThrower.hpp"
#include "NinjaAnt.hpp"
#include "Place.hpp"
#include "QueenAnt.hpp"
#include "ScaryThrower.hpp"
#include "ScubaThrower.hpp"
#include "ShortThrower.hpp"
#include "SlowThrower.hpp"
#include "TankAnt.hpp"
#include "WallAnt.hpp"

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

/**
 * @brief 序列化当前 Ant
 *
 * @return 当前 Ant 的序列化 JSON 对象。
 */
json Ant::serialize() const {
    json j = Insect::serialize();
    j["buffed"] = buffed;
    return j;
}

/**
 * @brief 从 JSON 对象反序列化得到 Ant
 *
 * @param data Ant 的 JSON 对象。
 * @return 反序列化得到的 Ant 指针。
 */
Ant *Ant::deserialize(const json &data) {
    string type = data["type"];
    double health = data["health"];
    Ant *ant = nullptr;
    if (type == "BodyguardAnt") { // ContainerAnt
        ant = new BodyguardAnt(health);
        dynamic_cast<ContainerAnt *>(ant)->storeAnt(Ant::deserialize(data["antContained"]));
    } else if (type == "FireAnt") {
        ant = new FireAnt(health);
    } else if (type == "HarvestAnt") {
        ant = new HarvestAnt(health);
    } else if (type == "HungryAnt") { // HungryAnt
        ant = new HungryAnt(health);
        dynamic_cast<HungryAnt *>(ant)->chewCountDown = data["chewCountDown"];
    } else if (type == "LaserAnt") { // LaserAnt
        ant = new LaserAnt(health);
        dynamic_cast<LaserAnt *>(ant)->insectsShot = data["insectsShot"];
    } else if (type == "LongThrower") {
        ant = new LongThrower(health);
    } else if (type == "NinjaAnt") {
        ant = new NinjaAnt(health);
    } else if (type == "QueenAnt") {
        ant = new QueenAnt(health);
    } else if (type == "ScaryThrower") {
        ant = new ScaryThrower(health);
    } else if (type == "ScubaThrower") {
        ant = new ScubaThrower(health);
    } else if (type == "ShortThrower") {
        ant = new ShortThrower(health);
    } else if (type == "SlowThrower") {
        ant = new SlowThrower(health);
    } else if (type == "TankAnt") { // ContainerAnt
        ant = new TankAnt(health);
        dynamic_cast<TankAnt *>(ant)->storeAnt(Ant::deserialize(data["antContained"]));
    } else if (type == "ThrowerAnt") {
        ant = new ThrowerAnt(health);
    } else if (type == "WallAnt") {
        ant = new WallAnt(health);
    }
    ant->buffed = data["buffed"];
    return ant;
}