#ifndef WASP_HPP
#define WASP_HPP

#include "Bee.hpp"

class Wasp : public Bee {
protected:
    [[nodiscard]]
    string getName() const override {
        return "Wasp";
    }
    [[nodiscard]]
    double getDefaultDamage() const override {
        return 2.0;
    }

public:
    explicit Wasp(double health, Place *place) : Bee(health, place) {}
    explicit Wasp(double health) : Wasp(health, nullptr) {}
};

#endif // WASP_HPP