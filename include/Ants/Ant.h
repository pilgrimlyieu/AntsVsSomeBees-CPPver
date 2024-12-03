#ifndef ANT_H
#define ANT_H

#include "Insect.h"

class Ant : public Insect {
public:
    inline static const string name = "Ant"; //!< 类名
    static const int foodCost = 0;           //!< 食物消耗
    static const bool isContainer = false;   //!< 是否可以容纳其他 Ant
    static const bool blocksPath = false;    //!< 是否阻挡路径
    bool buffed = false;                     //!< 是否被加成

    Ant(int health = 1);

    static Ant *construct(GameState &gamestate);

    void action(GameState &gamestate) override;

    void injuryCallback();

    void deathCallback();

    bool canContain(Ant *other);

    void storeAnt(Ant *other);

    void removeAnt(Ant *other);

    Ant &operator<<(Ant *other);

    Ant &operator>>(Ant *other);

    void addTo(Place *place);

    void removeFrom(Place *place);

    void buff();
};

#endif // ANT_H