#ifndef ANTREMOVER_H
#define ANTREMOVER_H

#include "Ant.h"

class AntRemover : public Ant {
public:
    string name = "Remover";       // the name of the Ant (Yeah, it's an Ant too)
    static const int foodCost = 1; // the food cost of the Remover (Everything has a cost)

    AntRemover(int health = 0);
};

#endif // ANTREMOVER_H