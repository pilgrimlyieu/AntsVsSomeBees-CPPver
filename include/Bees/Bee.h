#ifndef BEE_H
#define BEE_H

#include "Insect.h"

class Bee : public Insect {
private:
    inline static const std::string name = "Bee"; //!< 类名
    static const int damage = 1;                  //!< 伤害
    g_time slowedTime = 0;                        //!< 减速效果剩余时间
    g_time scaredTime = 0;                        //!< 恐惧效果剩余时间

public:
    static const bool isWaterProof = true; //!< 是否抗水

    explicit Bee(int health, Place *place = nullptr);

    void sting(Ant *ant);

    void moveTo(Place *place);

    bool blocked();

    void action(GameState &gamestate) override;

    void injuryCallback();

    void deathCallback();

    void addTo(Place *place) override;

    void removeFrom(Place *place) override;

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_H