#ifndef WASP_H
#define WASP_H

#include "Bee.hpp"

class Wasp : virtual public Bee {
public:
    explicit Wasp(double health, Place *place);

    explicit Wasp(double health) : Wasp(health, nullptr) {}
};

#endif // WASP_H