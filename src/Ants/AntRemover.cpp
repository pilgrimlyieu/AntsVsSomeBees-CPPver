#include "AntRemover.h"

/**
 * @brief 构造一个新的 AntRemover
 *
 * 默认 AntRemover 的属性：
 *
 * - 类名 name 为 "Remover"
 *
 * - 生命值 health 为 0.0
 *
 * - 食物消耗 foodCost 为 1
 */
AntRemover::AntRemover()
    : Ant(0.0, {
                   .name = "AntRemover",
                   .foodCost = 1,
               }) {}