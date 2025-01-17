#ifndef WASP_HPP
#define WASP_HPP

#include "Bee.hpp"

class Wasp : public Bee {
protected:
    virtual string getName() const override {
        return "Wasp";
    }
    virtual double getDefaultDamage() const override {
        return 1.0;
    }

public:
    explicit Wasp(double health, Place *place) : Bee(health, place) {}
    explicit Wasp(double health) : Wasp(health, nullptr) {}
};

#endif // WASP_HPP