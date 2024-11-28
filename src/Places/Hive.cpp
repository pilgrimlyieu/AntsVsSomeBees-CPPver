#include "Hive.h"

Hive::Hive() : Place("Hive", nullptr) {
    // TODO: Add `assaultPlan`
    // Always `nullptr` for a Hive
    this->entrance = nullptr;
    this->ant = nullptr;
}