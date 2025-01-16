#include "CLI.hpp"
#include "Server.hpp"
#include <nlohmann/json.hpp>


int main(int argc, char *argv[]) {
    CLI cli;
    CLIConfig cfg = cli.parse(argc, argv);

    int port = 18080;
    Server server(cfg, port);
    server.start();
    return 0;
}