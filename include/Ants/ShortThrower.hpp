#ifndef SHORTTHROWER_HPP
#define SHORTTHROWER_HPP

#include "ThrowerAnt.hpp"

class ShortThrower final : public ThrowerAnt {
public:
    explicit ShortThrower(double health);

    explicit ShortThrower() : ShortThrower(1.0) {}
};

#endif // SHORTTHROWER_HPP