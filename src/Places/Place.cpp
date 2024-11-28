#include "Place.h"
#include "Insect.h"

using namespace std;

Bee *Place::randomBee() {
    if (bees.size() == 0) {
        return nullptr;
    }
    return get<Bee *>(bees, rand() % bees.size());
}

Place::Place(string name, Place *exit) {
    this->name = name;
    this->exit = exit;

    if (this->exit != nullptr) {
        this->exit->entrance = this;
    }
}

void Place::addInsect(Insect *insect) {
    insect->addTo(this);
}

void Place::removeInsect(Insect *insect) {
    insect->removeFrom(this);
}

void Place::operator<<(Insect *insect) {
    this->addInsect(insect);
}

void Place::operator>>(Insect *insect) {
    this->removeInsect(insect);
}

Place::operator string() const {
    return name;
}

Place::~Place() {}