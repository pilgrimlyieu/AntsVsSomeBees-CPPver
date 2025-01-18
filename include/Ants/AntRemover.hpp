#ifndef ANTREMOVER_HPP
#define ANTREMOVER_HPP

#include "Ant.hpp"
#include "ContainerAnt.hpp"
#include "Place.hpp"

class AntRemover final : public Ant {
protected:
    string getName() const final {
        return "AntRemover";
    }
    int getFoodCost() const final {
        return 0;
    }

public:
    explicit AntRemover() : Ant(0.0) {}

    bool getIsWaterProof() const final {
        return true;
    }

    void addTo(Place *place) final {
        if (place->ant != nullptr) {
            auto container = dynamic_cast<ContainerAnt *>(place->ant);
            if (container && container->antContained) {
                Ant *contained = container->antContained;
                container->kill();
            } else {
                place->ant->kill();
            }
        }
    }
};

#endif // ANTREMOVER_HPP