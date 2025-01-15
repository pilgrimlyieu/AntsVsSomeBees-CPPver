#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "AntFactory.hpp"
#include "AntHomeBase.hpp"
#include "Hive.hpp"
#include "QueenAnt.hpp"

class GameState final {
private:
    using insects_list = vector<Insect *>;
    using ants_list = vector<Ant *>;
    using places_map = unordered_map<string, Place *>;
    using register_place_f = function<void(Place *, bool)>;
    using create_places = void (*)(AntHomeBase *, register_place_f, dim);

    friend void createLayout(AntHomeBase *base, GameState::register_place_f registerPlace,
                             dim dimensions, int moatFrequency);
    friend void wetLayout(AntHomeBase *base, GameState::register_place_f registerPlace,
                          dim dimensions);
    friend void dryLayout(AntHomeBase *base, GameState::register_place_f registerPlace,
                          dim dimensions);

public:
    g_time time = TIME_START;    //!> 时间
    int food = 0;                //!> 食物余额
    Hive *beehive;               //!> 蜂巢
    dim dimensions;              //!> 地图尺寸
    bees_list activeBees = {};   //!> 活动 Bee
    QueenAnt *Queen = nullptr;   //!> QueenAnt
    AntHomeBase *base = nullptr; //!> 基地
    places_map places;           //!> 地点
    AntFactory *antFactory;      //!> Ant 工厂
    places_list bee_entrances;   //!> Bee 入口

    GameState(Hive *beehive, create_places createPlaces, dim dimensions, int food = 2);

    void configure(Hive *beehive, create_places createPlaces);

    void antsTakeActions();

    void beesTakeActions();

    Generator<optional<bool>> simulate();

    Ant *deployAnt(string placeName, string antTypeName);

    void removeAnt(string placeName);

    [[nodiscard]]
    ants_list getAnts() const;

    [[nodiscard]]
    bees_list getBees() const;

    [[nodiscard]]
    insects_list getInsects() const;

    void createLayout(bool isWet);

    operator string() const;
};

template <> struct std::formatter<GameState> : std::formatter<string> {
    auto format(const GameState &gamestate, format_context &ctx) const {
        return std::formatter<string>::format(static_cast<string>(gamestate), ctx);
    }
};

void antsWin();

void antsLose();

void createLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions,
                  int moatFrequency = 3);

void wetLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions);

void dryLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions);

#endif // GAMESTATE_HPP