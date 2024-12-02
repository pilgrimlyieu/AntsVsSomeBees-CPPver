#include "Water.h"
#include "Insect.h"

/**
 * @brief Adds an insect to the water place.
 *
 * This function adds an insect to the water place by calling the base class
 * Place's addInsect method. If the insect is not waterproof, it will be killed.
 *
 * @param insect A pointer to the Insect object to be added.
 */
void Water::addInsect(Insect *insect) {
    Place::addInsect(insect);
    if (!insect->isWaterProof) {
        insect->kill();
    }
}