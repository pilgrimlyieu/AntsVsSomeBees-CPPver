#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "Libraries.hpp"

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual json serialize() const = 0;
    static Serializable *deserialize(const json &data);
};

#endif
