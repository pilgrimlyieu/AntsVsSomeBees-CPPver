#include "NinjaBee.hpp"

/**
 * @brief 构造一个新的 NinjaBee
 *
 * 默认 NinjaBee 的属性：
 *
 * - 类名 name 为 "Ninja"
 *
 * @param health NinjaBee 的初始生命值
 * @param place 指向 NinjaBee 所在的 Place 的指针，默认为 `nullptr`
 */
NinjaBee::NinjaBee(double health, Place *place)
    : Bee(health, place,
          {
              .name = "Ninja",
          }) {}

/**
 * @brief 判断 NinjaBee 是否被阻挡
 *
 * @return NinjaBee 不会被阻挡，返回 `false`
 */
bool NinjaBee::blocked() {
    return false;
}