#include "SlowThrower.h"
#include "Bee.h"

/**
 * @brief Throws a slow effect at the target bee.
 *
 * This function applies a slow effect to the target bee. The slow effect lasts for a duration of 3
 * turns.
 *
 * @param target A pointer to the Bee object that will be slowed. If the target is nullptr, no
 * action is taken.
 */
void SlowThrower::throwAt(Bee *target) {
    if (target != nullptr) {
        target->slow(3);
    }
}