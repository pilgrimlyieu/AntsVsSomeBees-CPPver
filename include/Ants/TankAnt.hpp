#ifndef TANKANT_H
#define TANKANT_H

#include "ContainerAnt.hpp"

class TankAnt final : public ContainerAnt {
public:
    explicit TankAnt(double health);

    explicit TankAnt() : TankAnt(2.0) {}

    void action(GameState &gamestate) final;
};

#endif // TANKANT_H