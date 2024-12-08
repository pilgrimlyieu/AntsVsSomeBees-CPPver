#ifndef BEE_H
#define BEE_H

#include "Insect.h"
struct bee_properties : insect_properties {
    std::string name = "Bee";
    double damage = 1.0;
    bool isWaterProof = true;
};

class Bee : public Insect {
protected:
    g_time slowedTime; //!< 减速效果剩余时间
    g_time scaredTime; //!< 恐惧效果剩余时间

    void injuryCallback() override;

    void deathCallback() override;

public:
    explicit Bee(double health, Place *place = nullptr, bee_properties properties = {});

    void sting(Ant *ant);

    void moveTo(Place *place);

    virtual bool blocked();

    virtual void action(GameState &gamestate) override;

    void addTo(Place *place) override;

    void removeFrom(Place *place) override;

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_H