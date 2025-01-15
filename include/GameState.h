#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "AntFactory.h"
#include "AntHomeBase.h"
#include "Hive.h"
#include "QueenAnt.h"

class GameState final {
private:
    using insects_list = vector<Insect *>;
    using ants_list = vector<Ant *>;
    using places_map = unordered_map<string, Place *>;
    using register_place_f = function<void(Place *, bool)>;
    using create_places = void (*)(AntHomeBase *, register_place_f, dim);

    friend void wetLayout(Place *base, register_place_f registerPlace, int tunnels, int length,
                          int moatFrequency);
    friend void dryLayout(Place *base, register_place_f registerPlace, int tunnels, int length);

public:
    g_time time = TIME_START;      //!> 时间
    int food = 0;                  //!> 食物余额
    strat strategy;                //!> 游戏策略
    Hive *beehive;                 //!> 蜂巢
    dim dimensions;                //!> 地图尺寸
    bees_list activeBees = {};     //!> 活动 Bee
    QueenAnt *Queen = nullptr;     //!> QueenAnt
    AntHomeBase *base = nullptr;   //!> 基地
    places_map places;             //!> 地点
    AntFactory *antFactory;        //!> Ant 工厂
    places_list bee_entrances;     //!> Bee 入口

    GameState(strat strategy, AntFactory *antFactory, Hive *beehive, create_places createPlaces,
              dim dimensions, int food = 2);

    void configure(Hive *beehive, create_places createPlaces);

    bool simulate();

    Ant *deployAnt(string placeName, string antTypeName);

    void removeAnt(string placeName);

    [[nodiscard]]
    ants_list getAnts() const;

    [[nodiscard]]
    bees_list getBees() const;

    [[nodiscard]]
    insects_list getInsects() const;

    operator string() const;
};

template <> struct std::formatter<GameState> : std::formatter<string> {
    auto format(const GameState &gamestate, format_context &ctx) const {
        return std::formatter<string>::format(static_cast<string>(gamestate), ctx);
    }
};

void antsWin();

void antsLose();

void wetLayout(Place *base, GameState::register_place_f registerPlace, int tunnels = 3,
               int length = 9, int moatFrequency = 3);

void dryLayout(Place *base, GameState::register_place_f registerPlace, int tunnels = 3,
               int length = 9);

#endif // GAMESTATE_H