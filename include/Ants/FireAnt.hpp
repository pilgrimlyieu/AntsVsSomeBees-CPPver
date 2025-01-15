#ifndef FIREANT_HPP
#define FIREANT_HPP

#include "Ant.hpp"

class FireAnt final : public Ant {
public:
    explicit FireAnt(double health);

    explicit FireAnt() : FireAnt(3.0) {}

    void reduceHealth(double amount) final;
};

#endif // FIREANT_HPP