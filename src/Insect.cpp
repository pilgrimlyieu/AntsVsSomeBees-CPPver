#include "Insect.h"
#include "Place.h"

/**
 * @brief Insect 类的构造函数，初始化一个 Insect
 *
 * 默认 Insect 的属性：
 *
 * - 类名 name 为 "Insect"
 *
 * - 伤害 damage 为 0.0
 *
 * - 是否抗水 isWaterProof 为 false
 *
 * @param health Insect 的初始生命值
 * @param place Insect 所在的 Place，默认为 nullptr
 * @param properties Insect 的属性
 */
Insect::Insect(double health, Place *place, insect_properties properties)
    : name(properties.name), damage(properties.damage), place(place), health(health),
      isWaterProof(properties.isWaterProof) {}

/**
 * @brief 减少 Insect 的生命值
 *
 * 减少 Insect 的生命值，并在生命值小于等于 0 时使 Insect 死亡。
 *
 * @param amount 要减少的生命值
 */
void Insect::reduceHealth(double amount) {
    health -= amount;
    injuryCallback();
    log(LOGINFO, format("{} is reduced by {}", string(*this), amount));
    if (health <= 0.0) {
        deathCallback();
        place->removeInsect(this);
        log(LOGINFO, format("{} is dead", string(*this)));
        delete this;
    }
}

/**
 * @brief 受伤回调函数
 *
 * 当 Insect 受伤时调用此函数。
 */
void Insect::injuryCallback() {
    // TODO
}

/**
 * @brief 死亡回调函数
 *
 * 当 Insect 死亡时调用此函数。
 */
void Insect::deathCallback() {
    // TODO
}

/**
 * @brief 将该 Insect 添加到指定的 Place
 *
 * @param place 指向 Place 的指针。
 */
void Insect::addTo(Place *place) {
    log(LOGINFO, format("{} is added to {}", string(*this), string(*place)));
    this->place = place;
}

/**
 * @brief 从指定的 Place 中移除 Insect
 *
 * @param place 要从中移除 Insect 的 Place 。
 */
void Insect::removeFrom(Place *place) {
    log(LOGINFO, format("{} is removed from {}", string(*this), string(*place)));
    this->place = nullptr;
}

/**
 * @brief 将 Insect 转换为字符串表示形式
 *
 * 该操作符重载函数将 Insect 转换为一个字符串，格式为 "name(health, damage)"。
 *
 * @return string 表示 Insect 的字符串。
 */
Insect::operator string() const {
    return format("{}({}, {})", name, health, damage);
}

/**
 * @brief 杀死该 Insect
 */
void Insect::kill() {
    reduceHealth(health);
}

/**
 * @brief 获取 Insect 的名称
 *
 * @return string Insect 的名称
 */
string Insect::getName() const {
    return name;
}