#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "AntFactory.h"
#include "AntHomeBase.h"
#include "Hive.h"
#include "QueenAnt.h"
#include "Utilities.h"

class GameState final {
private:
    using register_place = function<void(Place *, bool)>;
    using create_places = void (*)(AntHomeBase *, register_place, dim);
    using ants_map = unordered_map<string, function<Ant *(double)>>;

public:
    g_time time = TIME_START;              //!> 时间
    int food = 0;                          //!> 食物余额
    strat strategy;                        //!> 游戏策略
    Hive *beehive;                         //!> 蜂巢
    dim dimensions;                        //!> 地图尺寸
    list<Bee *> activeBees = {};           //!> 活动 Bee
    QueenAnt *Queen = nullptr;             //!> QueenAnt
    AntHomeBase *base = nullptr;           //!> 基地
    unordered_map<string, Place *> places; //!> 地点
    AntFactory *antFactory;                //!> Ant 工厂
    vector<Place *> bee_entrances;         //!> Bee 入口

    GameState(strat strategy, AntFactory *antFactory, Hive *beehive, create_places createPlaces,
              dim dimensions, int food = 2);

    void configure(Hive *beehive, create_places createPlaces);

    bool simulate();

    Ant *deployAnt(string placeName, string antTypeName);

    void removeAnt(string placeName);

    vector<Ant *> getAnts() const;

    vector<Bee *> getBees() const;

    vector<Insect *> getInsects() const;

    operator string() const;
};

void antsWin();

void antsLose();

#endif // GAMESTATE_H