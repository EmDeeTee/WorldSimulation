#ifndef CONFIG_H
#define CONFIG_H


#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"

enum FIELD {
    TICKSPEED,
    VERBOSE
};

void ReadConfigFile();

std::string ReadConfigValue(FIELD f);
bool IsVerbose();

#endif