#include "Server.hpp"
#include "Water.hpp"
#include "WebSocket.hpp"

/**
 * @brief 构造一个新的 Server
 *
 * @param config CLI 配置
 * @param port 服务器端口，默认为 18080
 */
Server::Server(CLIConfig config, int port) : config(std::move(config)), gameState(nullptr), game() {
    app.port(port).multithreaded().loglevel(crow::LogLevel::Info);
    setupRoutes();
    createNewGame();
}

/**
 * @brief 创建新游戏
 *
 * 创建一个新的游戏。
 */
void Server::createNewGame() {
    gameState = make_unique<GameState>(createGameState(config));
    game = gameState->simulate();
}

/**
 * @brief 设置路由
 *
 * - `GET /`：返回游戏开始信息
 *
 * - `POST /initialize_game`：返回游戏初始化信息
 *
 * - `GET /update_stats`：返回游戏状态信息
 *
 * - `POST /deploy_ants`：部署 Ant
 *
 * - `GET /ws`：WebSocket 服务
 *
 * - `GET /ants_take_actions`： Ant 行动
 *
 * - `GET /bees_take_actions`： Bee 行动
 */
void Server::setupRoutes() {
    CROW_ROUTE(app, "/")([this]() {
        std::cout << "\n ===== New Game Started ===== \n";
        createNewGame();
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

    CROW_ROUTE(app, "/initialize_game").methods("POST"_method)([this](const crow::request &req) {
        game.next();

        crow::json::wvalue response;
        response["dimensions_x"] = gameState->dimensions.first;
        response["dimensions_y"] = gameState->dimensions.second;

        vector<string> antTypes = AntFactory::getInstance().getAntNames();
        response["ant_types"] = std::move(antTypes);

        vector<vector<int>> wetPlaces;
        for (const auto &[name, place] : gameState->places) {
            if (dynamic_cast<Water *>(place)) {
                wetPlaces.emplace_back(parseCoordinates(name));
            }
        }
        response["wet_places"] = std::move(wetPlaces);

        return crow::response{response};
    });

    CROW_ROUTE(app, "/update_stats")([this] {
        crow::json::wvalue response;
        response["food"] = gameState->food;
        response["turn"] = gameState->time;

        vector<string> availableAnts;
        for (const auto &antName : AntFactory::getInstance().getAntNames()) {
            if (Ant *temp = AntFactory::getInstance().createAnt(antName)) {
                if (temp->getFoodCost() <= gameState->food) {
                    availableAnts.push_back(antName);
                }
                delete temp;
            }
        }
        response["available_ants"] = std::move(availableAnts);

        return crow::response{response};
    });

    CROW_ROUTE(app, "/deploy_ants").methods("POST"_method)([this](const crow::request &req) {
        auto data = crow::json::load(req.body);
        string pos = data["pos"].s();
        string antName = data["ant"].s();

        auto coords = split(pos, '-');
        string tunnel = format("Tunnel_{}_{}", coords[0], coords[1]);

        crow::json::wvalue response;
        response["deployed"] = false;

        try {
            if (Ant *ant = gameState->deployAnt(tunnel, antName)) {
                response["deployed"] = true;
                response["insect_id"] = ant->getId();
            }
        } catch (const out_of_range &) {
            tunnel = format("Water_{}_{}", coords[0], coords[1]);
            if (Ant *ant = gameState->deployAnt(tunnel, antName)) {
                response["deployed"] = true;
                response["insect_id"] = ant->getId();
            }
        }
        return crow::response{response};
    });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen(std::bind(&Server::handleWSOpen, this, std::placeholders::_1))
        .onclose(
            std::bind(&Server::handleWSClose, this, std::placeholders::_1, std::placeholders::_2))
        .onmessage(std::bind(&Server::handleWSMessage, this, std::placeholders::_1,
                             std::placeholders::_2, std::placeholders::_3));

    auto insectsTakeActions = [this]() {
        game.next();
        if (game.isGameOver()) {
            auto result = game.getResult();
            emitter.emit("endGame", {
                                        {"antsWon", result}
            });
        };
        // if (result && result.value().has_value()) {
        //     bool gameResult = result.value().value();
        //     emitter.emit("endGame", {
        //                                 {"antsWon", gameResult}
        //     });
        // }
        return crow::response(crow::status::OK);
    };

    CROW_ROUTE(app, "/ants_take_actions")(insectsTakeActions);

    CROW_ROUTE(app, "/bees_take_actions")(insectsTakeActions);
};

/**
 * @brief 处理 WebSocket 连接打开事件
 *
 * @param conn WebSocket 连接
 */
void Server::handleWSOpen(crow::websocket::connection &conn) {
    emitter.addConnection(&conn);
    crow::json::wvalue msg;
    msg["event"] = "loadLobby";
    msg["data"] = crow::json::wvalue();
    conn.send_text(msg.dump());
}

/**
 * @brief 处理 WebSocket 连接关闭事件
 *
 * @param conn WebSocket 连接
 * @param reason 关闭原因
 */
void Server::handleWSClose(crow::websocket::connection &conn, const string &reason) {
    emitter.removeConnection(&conn);
}

/**
 * @brief 处理 WebSocket 消息
 *
 * @param conn WebSocket 连接
 * @param data 消息数据
 * @param is_binary 是否为二进制消息
 */
void Server::handleWSMessage(crow::websocket::connection &conn, const string &data,
                             bool is_binary) {
    // Handle incoming WebSocket messages if needed
}

/**
 * @brief 启动服务器
 */
void Server::start() {
    app.run();
}