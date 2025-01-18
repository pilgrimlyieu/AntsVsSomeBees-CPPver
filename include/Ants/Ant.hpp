#ifndef ANT_HPP
#define ANT_HPP

#include "Insect.hpp"

class Ant : public Insect {
protected:
    bool buffed = false; //!< 是否被加成

public:
    explicit Ant(double health) : Insect(health, nullptr) {}
    explicit Ant() : Ant(1.0) {}

    virtual string getName() const override {
        return "Ant";
    }
    virtual int getFoodCost() const {
        return 0;
    }
    virtual bool getBlocksPath() const {
        return true;
    }
    double getDamage() const final {
        if (buffed) {
            return 2 * getDefaultDamage();
        } else {
            return getDefaultDamage();
        }
    }

    virtual void action(GameState &gamestate) override {};

    virtual bool canContain(Ant *other);

    virtual void storeAnt(Ant *other);

    virtual void removeAnt(Ant *other);

    void addTo(Place *place) final;

    void removeFrom(Place *place) override;

    void buff();

    virtual json serialize() const override;
    static Ant *deserialize(const json &data);
};

#endif // ANT_HPP