#ifndef PLACE_HPP
#define PLACE_HPP

#include "Serializable.hpp"
#include "Utilities.hpp"

class Place : public Serializable {
protected:
    ~Place() = default;

public:
    // exit <- place -> entrance --> Hive
    string name;         //!< 名称
    Place *exit;         //!< 出口（指向下一个 Place）
    Place *entrance;     //!< 入口（指向上一个 Place）
    bees_list bees = {}; //!< 在 Place 中的 Bee 列表
    Ant *ant = nullptr;  //!< 在 Place 中的 Ant

    Place(const Place &) = delete;
    Place &operator=(const Place &) = delete;
    Place(Place &&) = delete;
    Place &operator=(Place &&) = delete;

    explicit Place(string name, Place *exit);
    explicit Place(string name) : Place(name, nullptr) {}

    virtual bool getIsHive() const {
        return false;
    }

    Bee *randomBee();

    virtual void addInsect(Insect *insect);

    virtual void removeInsect(Insect *insect);

    operator string() const;

    virtual json serialize() const override;
    static Place *deserialize(const json &data);
};

template <std::derived_from<Place> T> struct std::formatter<T> : std::formatter<string> {
    auto format(const T &place, format_context &ctx) const {
        return std::formatter<string>::format(static_cast<string>(place), ctx);
    }
};

#endif // PLACE_HPP