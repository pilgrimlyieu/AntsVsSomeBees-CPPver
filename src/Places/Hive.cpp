#include "Hive.h"

/**
 * @brief 构造一个新的 Hive
 *
 * 初始化 Hive 的名称为 "Hive"，且不包含任何 Ant 。
 */
Hive::Hive() : Place("Hive", nullptr) {
    // TODO: Add `assaultPlan`
    // Always `nullptr` for a Hive
    this->entrance = nullptr;
    this->ant = nullptr;
}