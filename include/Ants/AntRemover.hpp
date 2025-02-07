#ifndef ANTREMOVER_HPP
#define ANTREMOVER_HPP

#include "Ant.hpp"
#include "Place.hpp"

class AntRemover final : public Ant {
protected:
    [[nodiscard]]
    string getName() const final {
        return "AntRemover";
    }
    [[nodiscard]]
    int getFoodCost() const final {
        return 0;
    }

public:
    explicit AntRemover() : Ant(0.0) {}

    [[nodiscard]]
    bool getIsWaterProof() const final {
        return true;
    }

    void addTo(Place *place) final {
        if (place->ant != nullptr) {
            if (place->ant->getName() != "QueenAnt") {
                place->ant->kill();
            } else {
                log(LOGERROR, "Cannot remove QueenAnt");
            }
        }
    }
};

#endif // ANTREMOVER_HPP