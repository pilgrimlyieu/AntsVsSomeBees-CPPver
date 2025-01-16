#include "Boss.hpp"

/**
 * @brief 构造一个新的 Boss
 *
 * 默认 Boss 的属性：
 *
 * - 类名 name 为 "Boss"
 *
 * @param health Boss 的初始生命值
 * @param place Boss 所在的 Place，默认为 `nullptr`
 */
Boss::Boss(double health, Place *place)
    : Bee(health, place,
          {
              .name = "Boss",
          }),
      Wasp(health, place), damageCap(8.0) {}

/**
 * @brief 计算伤害修正
 *
 * 伤害修正公式为 amount * damageCap / (damageCap + amount)
 *
 * damageCap 为伤害上限，默认值为 8.0
 *
 * @param amount 受到的攻击伤害
 */
double Boss::damageModifier(double amount) {
    return amount * damageCap / (damageCap + amount);
}

/**
 * @brief 减少 Boss 的生命值
 *
 * 修正受到的伤害后减少 Boss 的生命值。
 *
 * @param amount 要减少的生命值
 */
void Boss::reduceHealth(double amount) {
    Wasp::reduceHealth(damageModifier(amount));
}