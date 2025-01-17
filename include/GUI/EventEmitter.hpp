#ifndef EVENTEMITTER_HPP
#define EVENTEMITTER_HPP

#include "Utilities.hpp"

class EventEmitter {
private:
    vector<crow::websocket::connection *> connections; //!< WebSocket 连接

public:
    void emit(const string &event, const crow::json::wvalue &data);

    void addConnection(crow::websocket::connection *conn);

    void removeConnection(crow::websocket::connection *conn);
};

#endif // EVENTEMITTER_HPP
