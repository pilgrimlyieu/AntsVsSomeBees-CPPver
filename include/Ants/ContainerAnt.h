#ifndef CONTAINERANT_H
#define CONTAINERANT_H

#include "Ant.h"

class ContainerAnt : public Ant {
private:
    inline static const std::string name = "Container"; //!< 类名

protected:
    static const bool isContainer = true; //!< 是否可以容纳其他 Ant

    explicit ContainerAnt(int health = 1); //!< 抽象类，不可实例化

public:
    Ant *antContained; //!< 容纳的 Ant

    bool canContain(Ant *other) override;

    void storeAnt(Ant *ant) override;

    void removeAnt(Ant *ant) override;

    void removeFrom(Place *place) override;

    void action(GameState &gamestate) override;
};

#endif // CONTAINERANT_H