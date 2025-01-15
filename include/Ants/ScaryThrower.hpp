#ifndef SCARYTHROWER_HPP
#define SCARYTHROWER_HPP

#include "ThrowerAnt.hpp"

class ScaryThrower final : public ThrowerAnt {
private:
    void throwAt(Bee *target) final;

public:
    explicit ScaryThrower(double health);

    explicit ScaryThrower() : ScaryThrower(1.0) {}
};

#endif // SCARYTHROWER_HPP