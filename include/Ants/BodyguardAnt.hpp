#ifndef BODYGUARDANT_HPP
#define BODYGUARDANT_HPP

#include "ContainerAnt.hpp"

class BodyguardAnt final : public ContainerAnt {
public:
    explicit BodyguardAnt(double health);

    explicit BodyguardAnt() : BodyguardAnt(2.0) {}
};

#endif // BODYGUARDANT_HPP