#ifndef WATER_HPP
#define WATER_HPP

#include "Place.hpp"

class Water final : public Place {
public:
    using Place::Place;

    void addInsect(Insect *insect) final;

    json serialize() const final;
};

#endif // WATER_HPP