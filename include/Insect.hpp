#ifndef INSECT_HPP
#define INSECT_HPP

#include "Utilities.hpp"

struct insect_properties {
    string name = "Insect";    //!< 类名
    double damage = 0.0;       //!< 伤害
    bool isWaterProof = false; //!< 是否抗水
    Place *place;              //!< 所在地点
};
class Insect {
private:
protected:
    const string name; //!< 类名
    double damage;     //!< 伤害
    Place *place;      //!< 所在地点

    virtual void injuryCallback();

    virtual void deathCallback();

public:
    Insect(Insect &&) = delete;
    Insect &operator=(Insect &&) = delete;
    Insect(const Insect &) = delete;
    Insect &operator=(const Insect &) = delete;

    double health;           //!< 生命值
    const bool isWaterProof; //!< 是否抗水

    explicit Insect(double health, Place *place = nullptr, insect_properties properties = {});

    virtual void reduceHealth(double amount);

    virtual void action(GameState &gamestate) = 0; //!< 执行 Insect 的动作

    operator string() const;

    void kill();

    virtual void addTo(Place *place);

    virtual void removeFrom(Place *place);

    [[nodiscard]]
    string getName() const;

    virtual ~Insect() = default;
};

template <std::derived_from<Insect> T> struct std::formatter<T> : std::formatter<string> {
    auto format(const T &insect, std::format_context &ctx) const {
        return std::formatter<string>::format(static_cast<string>(insect), ctx);
    }
};

#endif // INSECT_HPP