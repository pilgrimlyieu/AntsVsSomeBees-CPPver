#ifndef BEE_H
#define BEE_H

#include "Insect.h"

class Bee : public Insect {
private:
    inline static const std::string name = "Bee"; //!< 类名

protected:
    constexpr static const double damage = 1.0; //!< 伤害
    g_time slowedTime = 0;                      //!< 减速效果剩余时间
    g_time scaredTime = 0;                      //!< 恐惧效果剩余时间

    void injuryCallback() override;

    void deathCallback() override;

public:
    static const bool isWaterProof = true; //!< 是否抗水

    explicit Bee(double health, Place *place = nullptr);

    void sting(Ant *ant);

    void moveTo(Place *place);

    virtual bool blocked();

    void action(GameState &gamestate) override;

    void addTo(Place *place) override;

    void removeFrom(Place *place) override;

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_H