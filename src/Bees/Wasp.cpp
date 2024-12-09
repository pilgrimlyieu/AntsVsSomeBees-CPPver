#include "Wasp.h"

/**
 * @brief 构造一个新的 Wasp
 *
 * 默认 Wasp 的属性：
 *
 * - 类名 name 为 "Wasp"
 *
 * - 伤害 damage 为 2.0
 *
 * @param health Wasp 的初始生命值
 * @param place 指向 Wasp 所在的 Place 的指针，默认为 `nullptr`
 */
Wasp::Wasp(double health, Place *place)
    : Bee(health, place,
          {
              .name = "Wasp",
              .damage = 2.0,
          }) {}