#ifndef INSECT_H
#define INSECT_H

#include "Utilities.h"

using namespace std;

class Insect {
public:
    inline static const string name = "Insect"; //!< 类名
    static const bool isWaterProof = false;     //!< 是否抗水
    int damage = 0;                             //!< 伤害
    int health;                                 //!< 生命值
    Place *place = nullptr;                     //!< 所在地点

    Insect(int health, Place *place);

    void reduceHealth(int amount);

    virtual void action(GameState &gamestate) = 0; //!< 执行 Insect 的动作

    void injuryCallback();

    void deathCallback();

    void addTo(Place *place);

    void removeFrom(Place *place);

    operator string() const;

    void kill();

    virtual ~Insect() = default;
};

#endif // INSECT_H