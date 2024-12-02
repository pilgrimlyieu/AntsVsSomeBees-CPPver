#include "Hive.h"

/**
 * @brief Constructs a Hive object.
 *
 * Initializes a Hive object with the name "Hive" and sets the entrance and ant pointers to nullptr.
 *
 * The assaultPlan is not added for a Hive, and it is always set to nullptr.
 */
Hive::Hive() : Place("Hive", nullptr) {
    // TODO: Add `assaultPlan`
    // Always `nullptr` for a Hive
    this->entrance = nullptr;
    this->ant = nullptr;
}