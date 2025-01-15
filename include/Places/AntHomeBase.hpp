#ifndef ANTHOMEBASE_H
#define ANTHOMEBASE_H

#include "Place.hpp"

class AntHomeBase final : public Place {
public:
    using Place::Place;

    void addInsect(Insect *insect) final;
};

#endif // ANTHOMEBASE_H