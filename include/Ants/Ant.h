#ifndef ANT_H
#define ANT_H

#include "Insect.h"

class Ant : public Insect {
  public:
    static const int foodCost = 0;         // the food cost of the Ant
    static const bool isContainer = false; // if the Ant is a Container
    static const bool blocksPath = false;  // if the Ant can block the path
    bool buffed;                           // if the Ant is buffed

    Ant(int health = 1);

    static Ant *construct(GameState &gamestate);

    void action(GameState &gamestate);

    void deathCallback();

    bool canContain(Ant *other);

    void storeAnt(Ant *other);

    void removeAnt(Ant *other);

    void addTo(Place *place);

    void removeFrom(Place *place);

    void buff();
};

#endif // ANT_H