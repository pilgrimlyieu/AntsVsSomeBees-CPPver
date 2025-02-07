#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "Libraries.hpp"

class Serializable {
public:
    virtual ~Serializable() = default;
    [[nodiscard]]
    virtual json serialize() const = 0;
    [[nodiscard]]
    static Serializable *deserialize(const json &data) = delete;
};

#endif
