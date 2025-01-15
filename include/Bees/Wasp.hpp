#ifndef WASP_HPP
#define WASP_HPP

#include "Bee.hpp"

class Wasp : virtual public Bee {
public:
    explicit Wasp(double health, Place *place);

    explicit Wasp(double health) : Wasp(health, nullptr) {}
};

#endif // WASP_HPP