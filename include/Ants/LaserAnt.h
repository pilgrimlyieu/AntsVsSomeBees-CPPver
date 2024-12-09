#ifndef LASERANT_H
#define LASERANT_H

#include "ThrowerAnt.h"

class LaserAnt final : public ThrowerAnt {
private:
    int insectsShot; //!< 射击的昆虫数量

    unordered_map<Insect *, int> getTargets();

    double getDamage(int distance);

public:
    explicit LaserAnt(double health);

    explicit LaserAnt() : LaserAnt(1.0) {}

    void action(GameState &gamestate) override final;
};

#endif // LASERANT_H{
