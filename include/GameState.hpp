#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "AntFactory.hpp"
#include "AntHomeBase.hpp"
#include "Hive.hpp"
#include "QueenAnt.hpp"

class Simulator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        Simulator get_return_object() {
            return Simulator{handle_type::from_promise(*this)};
        }
        std::suspend_always initial_suspend() {
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        void return_void() {}
        void unhandled_exception() {
            std::terminate();
        }

        std::suspend_always yield_value(std::nullptr_t) {
            is_game_over = false;
            return {};
        }

        std::suspend_always yield_value(bool value) {
            is_game_over = true;
            result = value;
            return {};
        }

        bool is_game_over = false;
        bool result = false;
    };

    explicit Simulator() : handle(nullptr) {}
    explicit Simulator(handle_type h) : handle(h) {}
    Simulator(Simulator &&other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }
    Simulator &operator=(Simulator &&other) noexcept {
        if (this != &other) {
            if (handle) {
                handle.destroy();
            }
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }
    ~Simulator() {
        if (handle) {
            handle.destroy();
        }
    }
    void next() {
        if (!handle.done()) {
            handle.resume();
        }
    }
    bool isGameOver() const {
        return handle.promise().is_game_over;
    }
    bool getResult() const {
        return handle.promise().result;
    }

private:
    handle_type handle;
};

class GameState final {
private:
    using insects_list = vector<Insect *>;
    using ants_list = vector<Ant *>;
    using places_map = unordered_map<string, Place *>;
    using register_place_f = function<void(Place *, bool)>;
    using create_places = void (*)(AntHomeBase *, register_place_f, dim);

    static void createLayout(AntHomeBase *base, GameState::register_place_f registerPlace,
                             dim dimensions, int moatFrequency = 3);

    friend void wetLayout(AntHomeBase *base, GameState::register_place_f registerPlace,
                          dim dimensions);
    friend void dryLayout(AntHomeBase *base, GameState::register_place_f registerPlace,
                          dim dimensions);

public:
    g_time time = TIME_START;    //!> 时间
    int food;                    //!> 食物余额
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

    Simulator simulate();

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

void wetLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions);

void dryLayout(AntHomeBase *base, GameState::register_place_f registerPlace, dim dimensions);

#endif // GAMESTATE_HPP