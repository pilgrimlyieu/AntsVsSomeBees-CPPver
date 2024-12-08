#ifndef ANTHOMEBASE_H
#define ANTHOMEBASE_H

#include "Place.h"

class AntHomeBase final : public Place {
public:
    explicit AntHomeBase(std::string name = "AntHomeBase", Place *exit = nullptr);

    void addInsect(Insect *insect) override final;
};

#endif // ANTHOMEBASE_H