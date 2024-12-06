#include "Insect.h"
#include "Place.h"

/**
 * @brief Insect 类的构造函数
 *
 * @param health 初始化 Insect 的生命值
 * @param place 指向 Place 的指针，用于初始化 Insect 的位置
 */
Insect::Insect(int health, Place *place) {
    this->health = health;
    this->place = place;
}

/**
 * @brief 减少 Insect 的生命值
 *
 * 减少 Insect 的生命值，并在生命值小于等于 0 时使 Insect 死亡。
 *
 * @param amount 要减少的生命值
 */
void Insect::reduceHealth(int amount) {
    health -= amount;
    injuryCallback();
    if (health <= 0) {
        deathCallback();
        place->removeInsect(this);
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
    this->place = place;
}

/**
 * @brief 从指定的 Place 中移除 Insect
 *
 * @param place 要从中移除 Insect 的 Place 。
 */
void Insect::removeFrom(Place *place) {
    this->place = nullptr;
}

/**
 * @brief 将 Insect 转换为字符串表示形式
 *
 * 该操作符重载函数将 Insect 转换为一个字符串，格式为 "name(health, damage)"。
 *
 * @return std::string 表示 Insect 的字符串。
 */
Insect::operator std::string() const {
    return string_format("%s(%d, %d)", name.c_str(), health, damage);
}

/**
 * @brief 杀死该 Insect
 */
void Insect::kill() {
    reduceHealth(health);
}