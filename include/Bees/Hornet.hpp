#ifndef HORNET_HPP
#define HORNET_HPP

#include "Bee.hpp"

class Hornet : virtual public Bee {
public:
    explicit Hornet(double health, Place *place);

    explicit Hornet(double health) : Hornet(health, nullptr) {}

    void action(GameState &gamestate) final;

    // TODO: immune
};

#endif // HORNET_HPP