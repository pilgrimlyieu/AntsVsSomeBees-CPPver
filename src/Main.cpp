#include "CLI.hpp"
#include "Server.hpp"

int main(int argc, char *argv[]) {
    programInit();
    try {
        CLI cli;
        CLIConfig cfg = cli.parse(argc, argv);
        Server server(cfg);
        server.start();
    } catch (const exception &e) {
        log(LOGERROR, e.what());
        return 1;
    }
    return 0;
}