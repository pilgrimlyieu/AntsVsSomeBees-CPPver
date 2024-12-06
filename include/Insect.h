#ifndef INSECT_H
#define INSECT_H

#include "Utilities.h"

class Insect {
private:
    inline static const std::string name = "Insect"; //!< 类名

protected:
    int damage = 0;         //!< 伤害
    Place *place = nullptr; //!< 所在地点

    void injuryCallback();

    void deathCallback();

public:
    int health;                             //!< 生命值
    static const bool isWaterProof = false; //!< 是否抗水

    explicit Insect(int health, Place *place);

    void reduceHealth(int amount);

    virtual void action(GameState &gamestate) = 0; //!< 执行 Insect 的动作

    operator std::string() const;

    void kill();

    virtual void addTo(Place *place);

    virtual void removeFrom(Place *place);

    virtual ~Insect() = default;
};

#endif // INSECT_H