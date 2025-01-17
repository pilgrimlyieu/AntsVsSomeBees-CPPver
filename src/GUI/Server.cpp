#include "Server.hpp"
#include "Bee.hpp"
#include "MakePlans.hpp"
#include "Water.hpp"
#include "WebSocket.hpp"

/**
 * @brief 构造一个新的 Server
 *
 * @param config CLI 配置
 * @param port 服务器端口，默认为 18080
 */
Server::Server(CLIConfig config) : config(std::move(config)), gameState(nullptr), game() {
    app.port(config.port).multithreaded().loglevel(crow::LogLevel::Critical);
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
        log(LOGINFO, "New game started");
        createNewGame();
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

    CROW_ROUTE(app, "/initialize_game").methods("POST"_method)([this](const crow::request &req) {
        game.next();

        auto response = getGameInfo();

        return crow::response{response};
    });

    CROW_ROUTE(app, "/update_stats")([this] {
        crow::json::wvalue response;
        response["food"] = gameState->food;
        response["turn"] = gameState->time;

        vector<string> availableAnts;
        for (const auto &antName : AntFactory::getInstance().getAntNames()) {
            if (AntFactory::getInstance().canDeployAnt(*gameState, antName)) {
                availableAnts.push_back(antName);
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
                if (ant != nullptr) {
                    response["deployed"] = true;
                    response["insect_id"] = ant->getId();
                }
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

    CROW_ROUTE(app, "/ants_take_actions")([this] { return handleInsectActions(); });

    CROW_ROUTE(app, "/bees_take_actions")([this] { return handleInsectActions(); });

    CROW_ROUTE(app, "/exit_game").methods("POST"_method)([this] {
        stop();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/save_game")([this] {
        if (!gameState) {
            return crow::response(404, "Game not found");
        }

        json response = gameState->serialize();
        std::string json_str = response.dump();
        return crow::response{json_str};
    });

    CROW_ROUTE(app, "/load_game").methods("POST"_method)([this](const crow::request &req) {
        try {
            resetGame();
            auto data = json::parse(req.body);
            auto newState = GameState::deserialize(data);

            gameState = make_unique<GameState>(std::move(newState));
            game = gameState->simulate();
            game.next();

            auto response = getGameInfo();

            vector<crow::json::wvalue> existingAnts;
            for (auto ant : gameState->getAnts()) {
                if (!ant->getPlace()) {
                    continue;
                }
                crow::json::wvalue antInfo;
                antInfo["type"] = ant->getName();
                antInfo["id"] = ant->getId();
                auto coords = parseCoordinates(ant->getPlace()->name);
                antInfo["pos"] = coords;
                existingAnts.push_back(std::move(antInfo));
            }
            response["existing_ants"] = std::move(existingAnts);

            vector<crow::json::wvalue> existingBees;
            for (auto bee : gameState->activeBees) {
                if (!bee->getPlace() || bee->getPlace()->getIsHive()) {
                    continue;
                }
                crow::json::wvalue beeInfo;
                beeInfo["type"] = bee->getName();
                beeInfo["id"] = bee->getId();
                auto coords = parseCoordinates(bee->getPlace()->name);
                beeInfo["pos"] = coords;
                existingBees.push_back(std::move(beeInfo));
            }
            response["existing_bees"] = std::move(existingBees);

            return crow::response{response};
        } catch (const std::exception &e) {
            return crow::response(400, e.what());
        }
    });
};

/**
 * @brief 处理 WebSocket 连接打开事件
 *
 * @param conn WebSocket 连接
 */
void Server::handleWSOpen(crow::websocket::connection &conn) {
    WebSocket::getEmitter().addConnection(&conn);
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
    WebSocket::getEmitter().removeConnection(&conn);
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
 * @brief 处理 Insect 动作
 *
 * @return HTTP 响应
 */
crow::response Server::handleInsectActions() {
    game.next();
    if (game.isGameOver()) {
        auto result = game.getResult();
        WebSocket::getEmitter().emit("endGame", {
                                                    {"antsWon", result}
        });
    };
    return crow::response{crow::json::wvalue()};
}

/**
 * @brief 启动服务器
 */
void Server::start() {
    log(LOGINFO,
        format("Server started at {1}http://localhost:{2}{0}", ANSI_RESET, ANSI_BOLD, app.port()));
    if (config.autoOpen) {
        string command;
#ifdef _WIN32
        command = format("start http://localhost:{0}", app.port());
#elif __APPLE__
        command = format("open http://localhost:{0}", app.port());
#else
        command = format("xdg-open http://localhost:{0}", app.port());
#endif
        system(command.c_str());
    }
    app.run();
}

/**
 * @brief 停止服务器
 */
void Server::stop() {
    WebSocket::getEmitter().emit("serverShutdown", crow::json::wvalue());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    app.stop();
}

crow::json::wvalue Server::getGameInfo() {
    crow::json::wvalue response;
    response["dimensions_x"] = gameState->dimensions.first;
    response["dimensions_y"] = gameState->dimensions.second;

    vector<crow::json::wvalue> antInfos;
    for (const auto &antName : AntFactory::getInstance().getAntNames()) {
        crow::json::wvalue antInfo;
        antInfo["type"] = antName;
        antInfo["food_cost"] = AntFactory::getInstance().getAntCost(antName);
        antInfos.push_back(std::move(antInfo));
    }
    response["ant_types"] = std::move(antInfos);

    vector<vector<int>> wetPlaces;
    for (const auto &[name, place] : gameState->places) {
        if (dynamic_cast<Water *>(place)) {
            wetPlaces.emplace_back(parseCoordinates(name));
        }
    }
    response["wet_places"] = std::move(wetPlaces);
    return response;
}

Server::~Server() {
    stop();
}