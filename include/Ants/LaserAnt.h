#ifndef LASERANT_H
#define LASERANT_H

#include "ThrowerAnt.h"

class LaserAnt final : public ThrowerAnt {
private:
    using insects_distance = unordered_map<Insect *, int>;

    int insectsShot; //!< 射击的昆虫数量

    insects_distance getTargets();

    double getDamage(int distance);

public:
    explicit LaserAnt(double health);

    explicit LaserAnt() : LaserAnt(1.0) {}

    void action(GameState &gamestate) final;
};

#endif // LASERANT_H{
