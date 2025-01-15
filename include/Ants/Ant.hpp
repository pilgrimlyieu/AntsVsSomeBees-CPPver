#ifndef ANT_HPP
#define ANT_HPP

#include "Insect.hpp"

#pragma clang diagnostic ignored \
    "-Wc99-designator" // mixture of designated and non-designated initializers in the same
                       // initializer list is a C99 extension

class Ant : public Insect {
protected:
    struct ant_properties : insect_properties {
        string name = "Ant";    //!< 类名
        int foodCost = 0;       //!< 食物消耗
        bool buffed = false;    //!< 是否被加成
        bool blocksPath = true; //!< 是否阻挡路径
    };

    bool buffed; //!< 是否被加成

    void injuryCallback() override;

    void deathCallback() override;

public:
    const int foodCost;    //!< 食物消耗
    const bool blocksPath; //!< 是否阻挡路径

    explicit Ant(double health, ant_properties properties);

    explicit Ant(double health) : Ant(health, {}) {}

    explicit Ant() : Ant(1.0) {}

    void action(GameState &gamestate) override;

    virtual bool canContain(Ant *other);

    virtual void storeAnt(Ant *other);

    virtual void removeAnt(Ant *other);

    void addTo(Place *place) final;

    void removeFrom(Place *place) override;

    void buff();
};

#endif // ANT_HPP