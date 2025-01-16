#ifndef BODYGUARDANT_HPP
#define BODYGUARDANT_HPP

#include "ContainerAnt.hpp"

class BodyguardAnt final : public ContainerAnt {
private:
    string getName() const final {
        return "BodyguardAnt";
    }
    int getFoodCost() const final {
        return 4;
    }

public:
    explicit BodyguardAnt(double health) : ContainerAnt(health) {}
    explicit BodyguardAnt() : BodyguardAnt(2.0) {}
};

#endif // BODYGUARDANT_HPP