#ifndef BEE_H
#define BEE_H

#include "Insect.h"

class Bee : public Insect {
  public:
    string name = "Bee";
    static const int damage = 1;
    static const bool isWaterProof = true;
    g_time slowedTime = 0;
    g_time scaredTime = 0;
    bool isScared = false;

    Bee(int health, Place *place = nullptr);

    void sting(Ant *ant);

    void moveTo(Place *place);

    bool blocked();

    void action(GameState &gamestate);

    void addTo(Place *place);

    void removeFrom(Place *place);

    void slow(g_time length);

    void scare(g_time length);
};

#endif // BEE_H