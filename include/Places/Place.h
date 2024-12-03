#ifndef PLACE_H
#define PLACE_H

#include "Utilities.h"

class Place {
public:
    // exit <- place -> entrance --> Hive
    string name = "Place";            //!< 名称
    static const bool isHive = false; //!< 是否是 Hive
    Place *exit;                      //!< 出口（指向下一个 Place）
    Place *entrance;                  //!< 入口（指向上一个 Place）
    list<Bee *> bees = {};            //!< 在 Place 中的 Bee 列表
    Ant *ant = nullptr;               //!< 在 Place 中的 Ant

    Bee *randomBee();

    Place(string name, Place *exit);

    void addInsect(Insect *insect);

    void removeInsect(Insect *insect);

    Place &operator<<(Insect *insect);

    Place &operator>>(Insect *insect);

    operator string() const;

    ~Place();
};

#endif // PLACE_H