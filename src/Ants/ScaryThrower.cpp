#include "ScaryThrower.h"
#include "Bee.h"

/**
 * @brief Throws a scare effect at the specified Bee target.
 *
 * This function applies a scare effect to the given Bee target, causing it to be scared for a
 * duration of 2 units.
 *
 * @param target A pointer to the Bee object to be scared. If the target is nullptr, the function
 * does nothing.
 */
void ScaryThrower::throwAt(Bee *target) {
    if (target != nullptr) {
        target->scare(2);
    }
}