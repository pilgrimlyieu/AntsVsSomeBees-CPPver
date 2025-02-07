#ifndef NINJABEE_HPP
#define NINJABEE_HPP

#include "Bee.hpp"

class NinjaBee final : public Bee {
protected:
    [[nodiscard]]
    string getName() const override {
        return "NinjaBee";
    }

public:
    explicit NinjaBee(double health, Place *place) : Bee(health, place) {}
    explicit NinjaBee(double health) : NinjaBee(health, nullptr) {}

    [[nodiscard]]
    bool blocked() final;
};

#endif // NINJABEE_HPP