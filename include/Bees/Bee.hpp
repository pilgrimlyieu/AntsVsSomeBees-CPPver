#ifndef BEE_HPP
#define BEE_HPP

#include "Insect.hpp"

class Bee : public Insect {
protected:
    [[nodiscard]]
    double getDefaultDamage() const override {
        return 1.0;
    }
    [[nodiscard]]
    bool getIsWaterProof() const override {
        return true;
    }

    g_time slowedTime = 0; //!< 减速效果剩余时间
    g_time scaredTime = 0; //!< 恐惧效果剩余时间

public:
    explicit Bee(double health, Place *place) : Insect(health, place) {}
    explicit Bee(double health) : Bee(health, nullptr) {}

    [[nodiscard]]
    string getName() const override {
        return "Bee";
    }

    void sting(Ant *ant);

    void moveTo(Place *place);

    [[nodiscard]]
    virtual bool blocked();

    void action(GameState &gamestate) override;

    void addTo(Place *place) override;

    void removeFrom(Place *place) override;

    void slow(g_time length);

    void scare(g_time length);

    [[nodiscard]]
    json serialize() const override;
    [[nodiscard]]
    static Bee *deserialize(const json &data);
};

#endif // BEE_HPP