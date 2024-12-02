#ifndef CONTAINERANT_H
#define CONTAINERANT_H

#include "Ant.h"

class ContainerAnt : public Ant {
public:
    string name = "Container";            // the name of the Ant
    static const bool isContainer = true; // if the Ant is a Container
    Ant *antContained;                    // the Ant contained in the container

    ContainerAnt(int health = 1);

    bool canContain(Ant *other);

    void storeAnt(Ant *ant);

    void removeAnt(Ant *ant);

    void removeFrom(Place *place);

    void action(GameState &gamestate);
};

#endif // CONTAINERANT_H