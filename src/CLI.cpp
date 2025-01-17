#include "CLI.hpp"
#include "Info.hpp"

CLI::CLI() : parser(ProjectInfo::PROJECT_NAME, ProjectInfo::VERSION) {
    parser.add_argument("-d", "--difficulty")
        .help("sets difficulty of game (test/easy/normal/hard/extra-hard)")
        .metavar("DIFFICULTY")
        .default_value(string("normal"))
        .choices("test", "easy", "normal", "hard", "extra-hard")
        .store_into(config.difficulty);

    parser.add_argument("-w", "--water")
        .help("loads a full layout with water")
        .flag()
        .store_into(config.waterEnabled);

    parser.add_argument("-f", "--food")
        .help("number of food to start with when testing")
        .metavar("FOOD")
        .default_value(2)
        .scan<'i', int>()
        .store_into(config.initialFood);
}

CLIConfig CLI::parse(int argc, char *argv[]) {
    try {
        parser.parse_args(argc, argv);
        return config;
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        std::exit(1);
    }
}