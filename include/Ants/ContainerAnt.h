#ifndef CONTAINERANT_H
#define CONTAINERANT_H

#include "Ant.h"

class ContainerAnt : public Ant {
private:
    inline static const std::string name = "Container"; //!< 类名

protected:
    static const bool isContainer = true; //!< 是否可以容纳其他 Ant

    explicit ContainerAnt(double health = 1.0); //!< 抽象类，不可实例化

public:
    Ant *antContained; //!< 容纳的 Ant

    bool canContain(Ant *other) override final;

    void storeAnt(Ant *ant) override final;

    void removeAnt(Ant *ant) override final;

    void removeFrom(Place *place) override final;

    void action(GameState &gamestate) override;
};

#endif // CONTAINERANT_H