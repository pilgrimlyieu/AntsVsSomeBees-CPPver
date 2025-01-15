#ifndef BEE_HPP
#define BEE_HPP

#include "Insect.hpp"

class Bee : public Insect {
protected:
    struct bee_properties : insect_properties {
        string name = "Bee";
        double damage = 1.0;
        bool isWaterProof = true;
    };

    g_time slowedTime; //!< 减速效果剩余时间
    g_time scaredTime; //!< 恐惧效果剩余时间

public:
    explicit Bee(double health, Place *place, bee_properties properties);

    explicit Bee(double health, Place *place) : Bee(health, place, {}) {}

    explicit Bee(double health) : Bee(health, nullptr) {}

    void sting(Ant *ant);

    void moveTo(Place *place);

    virtual bool blocked();

    void action(GameState &gamestate) override;

    void addTo(Place *place) override;

    void removeFrom(Place *place) override;

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_HPP