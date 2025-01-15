#ifndef NINJAANT_HPP
#define NINJAANT_HPP

#include "Ant.hpp"

class NinjaAnt final : public Ant {
public:
    explicit NinjaAnt(double health);

    explicit NinjaAnt() : NinjaAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // NINJAANT_HPP