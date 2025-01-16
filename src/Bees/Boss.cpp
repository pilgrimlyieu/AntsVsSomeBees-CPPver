#include "Boss.hpp"

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