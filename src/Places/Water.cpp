#include "Water.h"
#include "Insect.h"

void Water::addInsect(Insect *insect) {
    Place::addInsect(insect);
    if (!insect->isWaterProof) {
        insect->kill();
    }
}