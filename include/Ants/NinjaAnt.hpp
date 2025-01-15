#ifndef NINJAANT_H
#define NINJAANT_H

#include "Ant.hpp"

class NinjaAnt final : public Ant {
public:
    explicit NinjaAnt(double health);

    explicit NinjaAnt() : NinjaAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // NINJAANT_H