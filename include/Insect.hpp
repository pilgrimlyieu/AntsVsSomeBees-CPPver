#ifndef INSECT_HPP
#define INSECT_HPP

#include "Serializable.hpp"
#include "Utilities.hpp"

class Insect : public Serializable {
private:
    static int idCounter; //!< Insect ID 计数器
    int id;               //!< Insect ID

protected:
    virtual double getDefaultDamage() const {
        return 0.0;
    }

    Place *place; //!< 所在地点

    void injuryCallback();

    void deathCallback();

public:
    Insect(Insect &&) = delete;
    Insect &operator=(Insect &&) = delete;
    Insect(const Insect &) = delete;
    Insect &operator=(const Insect &) = delete;

    double health; //!< 生命值

    explicit Insect(double health, Place *place = nullptr)
        : id(idCounter++), place(place), health(health) {}

    virtual void reduceHealth(double amount);

    virtual void action(GameState &gamestate) = 0; //!< 执行 Insect 的动作

    operator string() const;

    void kill();

    virtual void addTo(Place *place);

    virtual void removeFrom(Place *place);

    static void resetIdCounter();

    int getId() const;
    Place *getPlace() const;
    void setPlace(Place *place);

    [[nodiscard]]
    virtual string getName() const {
        return "Insect";
    }
    virtual double getDamage() const {
        return getDefaultDamage();
    }
    virtual bool getIsWaterProof() const {
        return false;
    }
    virtual json serialize() const override;

    virtual ~Insect() = default;
};

template <std::derived_from<Insect> T> struct std::formatter<T> : std::formatter<string> {
    auto format(const T &insect, std::format_context &ctx) const {
        return std::formatter<string>::format(static_cast<string>(insect), ctx);
    }
};

#endif // INSECT_HPP