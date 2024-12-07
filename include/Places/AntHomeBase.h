#ifndef ANTHOMEBASE_H
#define ANTHOMEBASE_H

#include "Place.h"

class AntHomeBase final : public Place {
private:
    inline static const std::string name = "AntHomeBase"; //!< 类名

public:
    void addInsect(Insect *insect) override final;
};

#endif // ANTHOMEBASE_H