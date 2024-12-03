#ifndef BEE_H
#define BEE_H

#include "Insect.h"

class Bee : public Insect {
public:
    inline static const string name = "Bee"; //!< 类名
    static const int damage = 1;             //!< 伤害
    static const bool isWaterProof = true;   //!< 是否抗水
    g_time slowedTime = 0;                   //!< 减速效果剩余时间
    g_time scaredTime = 0;                   //!< 恐惧效果剩余时间

    Bee(int health, Place *place = nullptr);

    void sting(Ant *ant);

    void moveTo(Place *place);

    bool blocked();

    void action(GameState &gamestate) override;

    void injuryCallback();

    void deathCallback();

    void addTo(Place *place);

    void removeFrom(Place *place);

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_H