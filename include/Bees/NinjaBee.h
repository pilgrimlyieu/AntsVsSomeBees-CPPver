#ifndef NINJABEE_H
#define NINJABEE_H

#include "Bee.h"

class NinjaBee final : public Bee {
public:
    explicit NinjaBee(double health = 1.0, Place *place = nullptr);

    bool blocked() override final;
};

#endif // NINJABEE_H