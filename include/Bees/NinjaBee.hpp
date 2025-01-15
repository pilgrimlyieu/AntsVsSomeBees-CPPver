#ifndef NINJABEE_HPP
#define NINJABEE_HPP

#include "Bee.hpp"

class NinjaBee final : public Bee {
public:
    explicit NinjaBee(double health, Place *place);

    explicit NinjaBee(double health) : NinjaBee(health, nullptr) {}

    bool blocked() final;
};

#endif // NINJABEE_HPP