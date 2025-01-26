#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include "EventEmitter.hpp"
#include "Place.hpp"
#include "ThrowerAnt.hpp"

class WebSocket {
private:
    static inline EventEmitter emitter; //!< 事件发射器

public:
    WebSocket() = delete;

    static EventEmitter &getEmitter();
    static void setEmitter(EventEmitter emitter);

    static void onInsectMove(Bee *bee, Place *place);
    static void onThrowerAttack(const ThrowerAnt *thrower, const Bee *target);
    static void onHealthReduced(const Insect *insect);
    static void onInsectDeath(const Insect *insect);
};

vector<int> parseCoordinates(const string &name);

#endif // WEBSOCKET_HPP