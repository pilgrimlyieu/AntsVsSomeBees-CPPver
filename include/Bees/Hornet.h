#ifndef HORNET_H
#define HORNET_H

#include "Bee.h"

class Hornet : virtual public Bee {
public:
    explicit Hornet(double health, Place *place);

    explicit Hornet(double health) : Hornet(health, nullptr) {}

    void action(GameState &gamestate) override final;

    // TODO: immune
};

#endif // HORNET_H