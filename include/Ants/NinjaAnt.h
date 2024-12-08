#ifndef NINJAANT_H
#define NINJAANT_H

#include "Ant.h"

class NinjaAnt final : public Ant {
public:
    explicit NinjaAnt(double health = 1.0);

    void action(GameState &gamestate) override final;
};

#endif // NINJAANT_H