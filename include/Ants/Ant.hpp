#ifndef ANT_HPP
#define ANT_HPP

#include "Insect.hpp"

class Ant : public Insect {
protected:
    bool buffed = false; //!< 是否被加成

public:
    explicit Ant(double health) : Insect(health, nullptr) {}
    explicit Ant() : Ant(1.0) {}

    [[nodiscard]]
    string getName() const override {
        return "Ant";
    }
    [[nodiscard]]
    virtual int getFoodCost() const {
        return 0;
    }
    [[nodiscard]]
    virtual bool getBlocksPath() const {
        return true;
    }
    [[nodiscard]]
    double getDamage() const final {
        if (buffed) {
            return 2 * getDefaultDamage();
        } else {
            return getDefaultDamage();
        }
    }

    void action(GameState &gamestate) override {};

    virtual bool canContain(Ant *other);

    virtual void storeAnt(Ant *other);

    virtual void removeAnt(Ant *other);

    void addTo(Place *place) override;

    void removeFrom(Place *place) override;

    void buff();

    [[nodiscard]]
    json serialize() const override;
    static Ant *deserialize(const json &data);
};

#endif // ANT_HPP