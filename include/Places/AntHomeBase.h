#ifndef ANTHOMEBASE_H
#define ANTHOMEBASE_H

#include "Place.h"

class AntHomeBase final : public Place {
public:
    using Place::Place;

    void addInsect(Insect *insect) override final;
};

#endif // ANTHOMEBASE_H