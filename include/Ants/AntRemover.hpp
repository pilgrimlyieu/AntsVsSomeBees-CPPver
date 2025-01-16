#ifndef ANTREMOVER_HPP
#define ANTREMOVER_HPP

#include "Ant.hpp"

class AntRemover final : public Ant {
protected:
    string getName() const final {
        return "AntRemover";
    }
    int getFoodCost() const final {
        return 1;
    }

public:
    explicit AntRemover() : Ant(0.0) {}
};

#endif // ANTREMOVER_HPP