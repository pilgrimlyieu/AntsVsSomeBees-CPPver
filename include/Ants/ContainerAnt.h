#ifndef CONTAINERANT_H
#define CONTAINERANT_H

#include "Ant.h"

class ContainerAnt : public Ant {
public:
    inline static const string name = "Container"; //!< 类名
    static const bool isContainer = true;          //!< 是否可以容纳其他 Ant
    Ant *antContained;                             //!< 容纳的 Ant

    ContainerAnt(int health = 1);

    bool canContain(Ant *other);

    void storeAnt(Ant *ant);

    void removeAnt(Ant *ant);

    void removeFrom(Place *place);

    void action(GameState &gamestate);
};

#endif // CONTAINERANT_H