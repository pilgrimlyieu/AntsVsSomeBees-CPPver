#ifndef PLACE_H
#define PLACE_H

#include "ThrowerAnt.h"
#include "Utilities.h"

struct place_properties {
    bool isHive = false; //!< 是否是 Hive
};

class Place {
public:
    // exit <- place -> entrance --> Hive
    std::string name;                 //!< 名称
    const bool isHive;                //!< 是否是 Hive
    Place *exit;                      //!< 出口（指向下一个 Place）
    Place *entrance;                  //!< 入口（指向上一个 Place）
    std::list<Bee *> bees = {};       //!< 在 Place 中的 Bee 列表
    Ant *ant = nullptr;               //!< 在 Place 中的 Ant

    explicit Place(std::string name, Place *exit = nullptr, place_properties properties = {});

    Bee *randomBee();

    virtual void addInsect(Insect *insect);

    virtual void removeInsect(Insect *insect);

    Place &operator<<(Insect *insect);

    Place &operator>>(Insect *insect);

    operator std::string() const;

    ~Place();
};

#endif // PLACE_H