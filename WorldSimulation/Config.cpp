#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "Config.h"
#include "Globals.h"


using json = nlohmann::json;
using std::cout; using std::cout;
namespace fs = std::filesystem;

std::string Config[2];

void ReadConfigFile() {
    cout << "Reading config file...\n";

    if (!fs::exists("config.json")) {
        cout << "[ERROR] CAN'T OPEN 'config.json'";
        getchar();
        exit(-1);
    }

    std::ifstream configFile("config.json");
    json data = json::parse(configFile);
    Config[0] = data["TickSpeedMs"].get <std::string>();
    Config[1] = data["Verbose"].get <std::string>();
}

std::string ReadConfigValue(FIELD f) {
    switch (f) {
        case TICKSPEED:
            return Config[0];
            break;
        case VERBOSE:
            return Config[1];
            break;
    }
}

bool IsVerbose() {
    if (Config[1] == "true") return true;
    else return false;
}
