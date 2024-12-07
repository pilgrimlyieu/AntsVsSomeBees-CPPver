#ifndef INSECT_H
#define INSECT_H

#include "Utilities.h"

class Insect {
private:
    inline static const std::string name = "Insect"; //!< 类名

protected:
    double damage = 0.0;    //!< 伤害
    Place *place = nullptr; //!< 所在地点

    virtual void injuryCallback();

    virtual void deathCallback();

public:
    double health;                          //!< 生命值
    static const bool isWaterProof = false; //!< 是否抗水

    explicit Insect(double health, Place *place);

    virtual void reduceHealth(int amount);

    virtual void action(GameState &gamestate) = 0; //!< 执行 Insect 的动作

    operator std::string() const;

    void kill();

    virtual void addTo(Place *place);

    virtual void removeFrom(Place *place);

    virtual ~Insect() = default;
};

#endif // INSECT_H