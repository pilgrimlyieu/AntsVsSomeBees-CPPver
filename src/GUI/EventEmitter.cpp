#include "EventEmitter.hpp"

/**
 * @brief 发送事件
 *
 * 发送事件到所有连接的 WebSocket 客户端。
 *
 * @param event 事件名
 * @param data 事件数据
 */
void EventEmitter::emit(const string &event, const crow::json::wvalue &data) {
    crow::json::wvalue msg;
    msg["event"] = event;
    msg["data"] = crow::json::wvalue(data);
    for (auto conn : connections) {
        conn->send_text(msg.dump());
    }
}

/**
 * @brief 添加连接
 *
 * 添加一个 WebSocket 连接。
 *
 * @param conn WebSocket 连接
 */
void EventEmitter::addConnection(crow::websocket::connection *conn) {
    connections.push_back(conn);
}

/**
 * @brief 移除连接
 *
 * 移除一个 WebSocket 连接。
 *
 * @param conn WebSocket 连接
 */
void EventEmitter::removeConnection(crow::websocket::connection *conn) {
    connections.erase(std::remove(connections.begin(), connections.end(), conn), connections.end());
}