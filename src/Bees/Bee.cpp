#include "Bee.h"
#include "Ant.h"
#include "GameState.h"
#include "Place.h"

/**
 * @brief 构造一个新的 Bee
 *
 * @param health Bee 的初始生命值，默认为 1
 * @param place 指向 Bee 所在的 Place 的指针，默认为 `nullptr`
 */
Bee::Bee(int health, Place *place) : Insect(health, place) {}

/**
 * @brief 对指定的 Ant 进行攻击
 *
 * 对指定的 Ant 进行攻击，使其减少生命值。
 *
 * @param ant 目标 Ant
 */
void Bee::sting(Ant *ant) {
    ant->reduceHealth(damage);
}

/**
 * @brief 将 Bee 移动到指定的 Place
 *
 * 将 Bee 从当前 Place 移动到指定的 Place 。
 *
 * @param place 指向要移动到的 Place 的指针。
 */
void Bee::moveTo(Place *place) {
    this->place->removeInsect(this);
    *place << this;
}

/**
 * @brief 判断 Bee 是否被阻挡
 *
 * @return 若 Bee 被阻挡，则返回 `true`；否则返回 `false`。
 */
bool Bee::blocked() {
    return place->ant != nullptr && place->ant->blocksPath;
}

/**
 * @brief 执行 Bee 的动作
 *
 * 在正常状态下 Bee 会尝试移动到下一个 Place 。若被阻挡则攻击当前 Place 中的 Ant 。
 *
 * 若 Bee 处于恐惧状态，则会尝试返回 Hive 。
 *
 * 若 Bee 处于减速状态，则每 2 个回合移动一次。
 *
 * @param gamestate 当前的游戏状态。
 */
void Bee::action(GameState &gamestate) {
    Place *destination = place->exit;
    if (scaredTime > 0) {
        destination = (place->entrance->isHive) ? place : place->entrance;
    }
    if (slowedTime > 0 && gamestate.time % 2 == 1) {
        slowedTime--;
    } else {
        slowedTime = std::max(TIME_START, slowedTime - 1);
        if (blocked()) {
            sting(place->ant);
        } else if (health > 0 && destination != nullptr) {
            moveTo(destination);
            scaredTime = std::max(TIME_START, scaredTime - 1);
        }
    }
}

/**
 * @brief 受伤回调函数
 *
 * 当 Bee 受伤时调用此函数。
 */
void Bee::injuryCallback() {
    // TODO
}

/**
 * @brief 死亡回调函数
 *
 * 当 Bee 死亡时调用此函数。
 */
void Bee::deathCallback() {
    // TODO
}

/**
 * @brief 将 Bee 添加到指定的 Place
 *
 * @param place 指向 Place 的指针。
 */
void Bee::addTo(Place *place) {
    place->bees.push_back(this);
    Insect::addTo(place);
}

/**
 * @brief 从指定的 Place 中移除 Bee
 *
 * @param place 指向要移除的 Place 的指针。
 */
void Bee::removeFrom(Place *place) {
    place->bees.remove(this);
    Insect::removeFrom(place);
}

/**
 * @brief 减速 Bee 一段时间
 *
 * 减速 Bee 一段时间，可以叠加。
 *
 * @param length 减速的时间长度。
 */
void Bee::slow(g_time length) {
    slowedTime += length;
}

/**
 * @brief 使 Bee 恐惧一段时间
 *
 * 使 Bee 恐惧一段时间，不能叠加。
 *
 * @param length 恐惧的时间长度。
 */
void Bee::scare(g_time length) {
    if (scaredTime == 0) {
        scaredTime = length;
    }
}
