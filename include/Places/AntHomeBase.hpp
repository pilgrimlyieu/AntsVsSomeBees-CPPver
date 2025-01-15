#ifndef ANTHOMEBASE_HPP
#define ANTHOMEBASE_HPP

#include "Place.hpp"

class AntHomeBase final : public Place {
public:
    using Place::Place;

    void addInsect(Insect *insect) final;
};

#endif // ANTHOMEBASE_HPP