#ifndef ANTFACTORY_HPP
#define ANTFACTORY_HPP

#include "Ant.hpp"
#include "QueenAnt.hpp"

class AntFactory {
private:
    using ant_constructor = function<Ant *()>;
    using constructors_map = map<string, ant_constructor>;

    static QueenAnt *queenAnt; //!> QueenAnt

    AntFactory() = default;
    ~AntFactory() = default;
    AntFactory &operator=(AntFactory &&) = delete;
    AntFactory(AntFactory &&) = delete;
    AntFactory(const AntFactory &) = delete;
    AntFactory &operator=(const AntFactory &) = delete;

    constructors_map antConstructors; //!> Ant 构造函数

public:
    static AntFactory &getInstance();

    void registerAnt(const string &name, ant_constructor constructor);

    [[nodiscard]]
    Ant *createAnt(const string &name) const;

    [[nodiscard]]
    vector<string> getAntNames() const;
};

#endif // ANTFACTORY_HPP