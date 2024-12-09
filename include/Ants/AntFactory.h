#ifndef ANTFACTORY_H
#define ANTFACTORY_H

#include "Ant.h"

class AntFactory {
private:
    using ant_constructor = function<Ant *()>;

    AntFactory() {}
    AntFactory(const AntFactory &) = delete;
    AntFactory &operator=(const AntFactory &) = delete;

    map<string, ant_constructor> antConstructors; //!> Ant 构造函数

public:
    static AntFactory &getInstance();

    void registerAnt(const string &name, ant_constructor constructor);

    Ant *createAnt(const string &name) const;

    vector<string> getAntNames() const;
};

#endif // ANTFACTORY_H