#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.hpp"

class FireAnt final : public Ant {
public:
    explicit FireAnt(double health);

    explicit FireAnt() : FireAnt(3.0) {}

    void reduceHealth(double amount) final;
};

#endif // FIREANT_H