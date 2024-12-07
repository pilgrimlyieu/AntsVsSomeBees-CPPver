#include "Boss.h"

/**
 * @brief 计算伤害修正
 *
 * 伤害修正公式为 amount * damageCap / (damageCap + amount)
 *
 * damageCap 为伤害上限，默认值为 8.0
 *
 * @param amount 受到的攻击伤害
 */
double Boss::damageModifier(int amount) {
    return amount * damageCap / (damageCap + amount);
}

void Boss::reduceHealth(int amount) {
    Wasp::reduceHealth(damageModifier(amount));
}