#ifndef ANTFACTORY_HPP
#define ANTFACTORY_HPP

#include "Ant.hpp"
#include "QueenAnt.hpp"

class AntFactory {
private:
    using ant_constructor = function<Ant *()>;
    using constructors_map = map<string, ant_constructor>;
    using costs_map = map<string, int>;

    static QueenAnt *queenAnt; //!> QueenAnt

    AntFactory() = default;
    ~AntFactory() = default;
    AntFactory &operator=(AntFactory &&) = delete;
    AntFactory(AntFactory &&) = delete;
    AntFactory(const AntFactory &) = delete;
    AntFactory &operator=(const AntFactory &) = delete;

    constructors_map antConstructors; //!> Ant 构造函数
    costs_map antCosts;               //!> Ant 食物消耗

public:
    static AntFactory &getInstance();

    static void resetQueenAnt();

    void registerAnt(const string &name, ant_constructor constructor, int foodCost);

    int getAntCost(const string &name) const;

    bool canDeployAnt(GameState &gameState, const string &name) const;

    [[nodiscard]]
    Ant *createAnt(const string &name) const;

    [[nodiscard]]
    vector<string> getAntNames() const;
};

#endif // ANTFACTORY_HPP