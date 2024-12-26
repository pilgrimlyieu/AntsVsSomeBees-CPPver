#ifndef ANTFACTORY_H
#define ANTFACTORY_H

#include "Ant.h"
#include "QueenAnt.h"

class AntFactory {
private:
    using ant_constructor = function<Ant *()>;
    using constructor_map = map<string, ant_constructor>;

    static QueenAnt *queenAnt; //!> QueenAnt

    AntFactory() = default;
    ~AntFactory() = default;

    constructor_map antConstructors; //!> Ant 构造函数

public:
    AntFactory &operator=(AntFactory &&) = delete;
    AntFactory(AntFactory &&) = delete;
    AntFactory(const AntFactory &) = delete;
    AntFactory &operator=(const AntFactory &) = delete;

    static AntFactory &getInstance();

    void registerAnt(const string &name, ant_constructor constructor);

    [[nodiscard]]
    Ant *createAnt(const string &name) const;

    [[nodiscard]]
    vector<string> getAntNames() const;
};

#endif // ANTFACTORY_H