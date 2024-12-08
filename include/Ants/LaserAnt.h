#ifndef LASERANT_H
#define LASERANT_H

#include "ThrowerAnt.h"

class LaserAnt final : public ThrowerAnt {
private:
    int insectsShot; //!< 射击的昆虫数量

    std::unordered_map<Insect *, int> getTargets();

    double getDamage(int distance);

public:
    LaserAnt(double health = 1.0);

    void action(GameState &gamestate) override final;
};

#endif // LASERANT_H{
