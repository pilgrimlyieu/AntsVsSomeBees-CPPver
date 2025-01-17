#ifndef ANTREMOVER_HPP
#define ANTREMOVER_HPP

#include "Ant.hpp"

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

    bool canContain(Ant *other) final {
        return true;
    }

    void storeAnt(Ant *other) final {
        log(LOGINFO, format("Remove {}", *other));
        other->kill();
    }
};

#endif // ANTREMOVER_HPP