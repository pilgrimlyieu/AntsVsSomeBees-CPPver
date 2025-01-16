#include "Insect.hpp"
#include "Place.hpp"
#include "WebSocket.hpp"

int Insect::idCounter = 0;

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
    log(LOGINFO, format("{} is reduced by {}", *this, amount));
    if (health <= 0.0) {
        deathCallback();
        place->removeInsect(this);
        log(LOGINFO, format("{} is dead", *this));
        delete this;
    }
}

/**
 * @brief 受伤回调函数
 *
 * 当 Insect 受伤时调用此函数。
 */
void Insect::injuryCallback() {
    WebSocket::onHealthReduced(this);
}

/**
 * @brief 死亡回调函数
 *
 * 当 Insect 死亡时调用此函数。
 */
void Insect::deathCallback() {
    WebSocket::onInsectDeath(this);
}

/**
 * @brief 将该 Insect 添加到指定的 Place
 *
 * @param place 指向 Place 的指针。
 */
void Insect::addTo(Place *place) {
    if (place != nullptr) {
        log(LOGINFO, format("{} is added to {}", *this, *place));
    } else {
        log(LOGINFO, format("{} is added to nullptr", *this));
    }
    this->place = place;
}

/**
 * @brief 从指定的 Place 中移除 Insect
 *
 * @param place 要从中移除 Insect 的 Place 。
 */
void Insect::removeFrom(Place *place) {
    log(LOGINFO, format("{} is removed from {}", *this, *place));
    this->place = nullptr;
}

/**
 * @brief 将 Insect 转换为字符串表示形式
 *
 * 该操作符重载函数将 Insect 转换为一个字符串，格式为 "name[id](health, place)"。
 *
 * @return string 表示 Insect 的字符串。
 */
Insect::operator string() const {
    if (place == nullptr) {
        return format("{}[{}]({}, NULL)", getName(), id, health);
    } else {
        return format("{}[{}]({}, {})", getName(), id, health, *place);
    }
}

/**
 * @brief 杀死该 Insect
 */
void Insect::kill() {
    reduceHealth(health);
}

/**
 * @brief 重置 Insect 的 ID 计数器
 */
void Insect::resetIdCounter() {
    idCounter = 0;
}

/**
 * @brief 获取 Insect 的 ID
 *
 * @return int Insect 的 ID
 */
int Insect::getId() const {
    return id;
}

/**
 * @brief 获取 Insect 所在的 Place
 *
 * @return Place* 指向 Insect 所在的 Place 的指针
 */
Place *Insect::getPlace() const {
    return place;
}
