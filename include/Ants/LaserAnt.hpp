#ifndef LASERANT_HPP
#define LASERANT_HPP

#include "ThrowerAnt.hpp"

class LaserAnt final : public ThrowerAnt {
protected:
    string getName() const final {
        return "LaserAnt";
    }
    double getDefaultDamage() const final {
        return 2.0;
    }
    int getFoodCost() const final {
        return 10;
    }

    friend Ant *Ant::deserialize(const json &data);

    using insects_distance = unordered_map<Insect *, int>;

    int insectsShot = 0; //!< 射击的昆虫数量

    insects_distance getTargets();

    double getTrueDamage(int distance);

public:
    explicit LaserAnt(double health) : ThrowerAnt(health) {}
    explicit LaserAnt() : LaserAnt(1.0) {}

    void action(GameState &gamestate) final;

    json serialize() const final;
};

#endif // LASERANT_HPP{
