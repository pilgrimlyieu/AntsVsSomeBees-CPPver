#ifndef NINJABEE_H
#define NINJABEE_H

#include "Bee.h"

class NinjaBee final : public Bee {
public:
    explicit NinjaBee(double health, Place *place);

    explicit NinjaBee(double health) : NinjaBee(health, nullptr) {}

    bool blocked() final;
};

#endif // NINJABEE_H