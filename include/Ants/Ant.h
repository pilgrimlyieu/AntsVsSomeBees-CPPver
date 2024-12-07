#ifndef ANT_H
#define ANT_H

#include "Insect.h"

class Ant : public Insect {
private:
    inline static const std::string name = "Ant"; //!< 类名
    static const int foodCost = 0;                //!< 食物消耗

protected:
    static const bool isContainer = false; //!< 是否可以容纳其他 Ant
    bool buffed = false;                   //!< 是否被加成

    void injuryCallback() override;

    void deathCallback() override;

public:
    static const bool blocksPath = false; //!< 是否阻挡路径

    explicit Ant(double health = 1.0);

    virtual Ant *construct(GameState &gamestate);

    virtual void action(GameState &gamestate) override;

    virtual bool canContain(Ant *other);

    virtual void storeAnt(Ant *other);

    virtual void removeAnt(Ant *other);

    Ant &operator<<(Ant *other);

    Ant &operator>>(Ant *other);

    void addTo(Place *place) override final;

    virtual void removeFrom(Place *place) override;

    void buff();
};

#endif // ANT_H