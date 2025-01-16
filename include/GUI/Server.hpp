#ifndef SERVER_HPP
#define SERVER_HPP

#include "CLI.hpp"
#include "EventEmitter.hpp"
#include "GameState.hpp"

class Server {
private:
    CLIConfig config;                //!< CLI 配置
    unique_ptr<GameState> gameState; //!< 游戏状态
    Simulator game;                  //!< 游戏输出
    crow::SimpleApp app;             //!< Web 服务器
    EventEmitter emitter;            //!< 事件发射器

    void handleWSOpen(crow::websocket::connection &conn);
    void handleWSClose(crow::websocket::connection &conn, const string &reason);
    void handleWSMessage(crow::websocket::connection &conn, const string &data, bool is_binary);

public:
    explicit Server(CLIConfig config, int port = 18080);
    ~Server();

    void start();
    void stop();
    void setupRoutes();
    void createNewGame();
};

#endif // SERVER_HPP