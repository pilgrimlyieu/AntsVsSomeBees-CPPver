#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.h"

class FireAnt final : public Ant {
public:
    explicit FireAnt(double health = 3.0);

    void reduceHealth(double amount) override final;
};

#endif // FIREANT_H