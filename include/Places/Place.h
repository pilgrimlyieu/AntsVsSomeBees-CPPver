#ifndef PLACE_H
#define PLACE_H

#include "Utilities.h"

using namespace std;

class Place {
  public:
    static const bool isHive = false;
    string name = "Place";
    Place *exit;
    Place *entrance;
    list<Bee *> bees = {};
    Ant *ant = nullptr;

    Bee *randomBee();

    Place(string name, Place *exit);

    void addInsect(Insect *insect);

    void removeInsect(Insect *insect);

    void operator<<(Insect *insect);

    void operator>>(Insect *insect);

    operator string() const;

    ~Place();
};

#endif // PLACE_H