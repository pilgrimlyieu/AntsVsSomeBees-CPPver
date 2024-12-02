#ifndef PLACE_H
#define PLACE_H

#include "Utilities.h"

class Place {
public:
    // exit <- place -> entrance
    string name = "Place";            // the name of the Place
    static const bool isHive = false; // whether this place is a hive
    Place *exit;                      // the exit of the Place
    Place *entrance;                  // the entrance of the Place
    list<Bee *> bees = {};            // the bees in the Place
    Ant *ant = nullptr;               // the ant in the Place

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