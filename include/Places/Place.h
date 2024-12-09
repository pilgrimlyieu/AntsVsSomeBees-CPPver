#ifndef PLACE_H
#define PLACE_H

#include "Utilities.h"

class Place {
private:
    struct place_properties {
        bool isHive = false; //!< 是否是 Hive
    };

Place(const Place &) = delete;
Place &operator=(const Place &) = delete;

public:
    // exit <- place -> entrance --> Hive
    string name;           //!< 名称
    const bool isHive;     //!< 是否是 Hive
    Place *exit;           //!< 出口（指向下一个 Place）
    Place *entrance;       //!< 入口（指向上一个 Place）
    list<Bee *> bees = {}; //!< 在 Place 中的 Bee 列表
    Ant *ant = nullptr;    //!< 在 Place 中的 Ant

    explicit Place(string name, Place *exit, place_properties properties);

    explicit Place(string name, Place *exit) : Place(name, exit, {}) {}

    explicit Place(string name) : Place(name, nullptr) {}

    Bee *randomBee();

    virtual void addInsect(Insect *insect);

    virtual void removeInsect(Insect *insect);

    Place &operator<<(Insect *insect);

    Place &operator>>(Insect *insect);

    operator string() const;

    ~Place();
};

#endif // PLACE_H