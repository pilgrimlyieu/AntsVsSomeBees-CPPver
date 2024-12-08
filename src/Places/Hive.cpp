#include "Hive.h"

/**
 * @brief 构造一个新的 Hive
 *
 * 默认 Hive 的属性：
 *
 * - 是否是 Hive isHive 为 true
 *
 * 初始化 Hive 的名称为 "Hive"，且不包含任何 Ant 。
 */
Hive::Hive() : Place("Hive", nullptr, {.isHive = true}) {
    // TODO: Add `assaultPlan`
    // Always `nullptr` for a Hive
    this->entrance = nullptr;
    this->ant = nullptr;
}