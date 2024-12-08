#ifndef TANKANT_H
#define TANKANT_H

#include "ContainerAnt.h"

class TankAnt final : public ContainerAnt {
public:
    explicit TankAnt(double health = 2.0);

    void action(GameState &gamestate) override final;
};

#endif // TANKANT_H