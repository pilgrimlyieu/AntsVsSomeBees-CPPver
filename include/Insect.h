#ifndef INSECT_H
#define INSECT_H

#include "Utilities.h"

struct insect_properties {
    std::string name = "Insect"; //!< 类名
    double damage = 0.0;         //!< 伤害
    bool isWaterProof = false;   //!< 是否抗水
    Place *place;                //!< 所在地点
};

class Insect {
protected:
    const std::string name; //!< 类名
    double damage;          //!< 伤害
    Place *place;           //!< 所在地点

    virtual void injuryCallback();

    virtual void deathCallback();

public:
    double health;           //!< 生命值
    const bool isWaterProof; //!< 是否抗水

    explicit Insect(double health, Place *place = nullptr, insect_properties properties = {});

    virtual void reduceHealth(double amount);

    virtual void action(GameState &gamestate) = 0; //!< 执行 Insect 的动作

    operator std::string() const;

    void kill();

    virtual void addTo(Place *place);

    virtual void removeFrom(Place *place);

    virtual ~Insect() = default;
};

#endif // INSECT_H