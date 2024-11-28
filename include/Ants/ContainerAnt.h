#ifndef CONTAINERANT_H
#define CONTAINERANT_H

#include "Ant.h"

class ContainerAnt : public Ant {
  public:
    string name = "Container";
    static const bool isContainer = true;
    Ant *antContained;

    ContainerAnt(int health = 1);

    bool canContain(Ant *other);

    void storeAnt(Ant *ant);

    void removeAnt(Ant *ant);

    void removeFrom(Place *place);

    void action(GameState &gamestate);
};

#endif // CONTAINERANT_H