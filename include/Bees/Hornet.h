#ifndef HORNET_H
#define HORNET_H

#include "Bee.h"

class Hornet : virtual public Bee {
public:
    explicit Hornet(double health, Place *place = nullptr);

    void action(GameState &gamestate) override final;

    // TODO: __setattr__
};

#endif // HORNET_H