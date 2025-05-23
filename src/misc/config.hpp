#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

namespace he::config {
    static std::unordered_map<std::string, std::string> store;

    void loadFromFile(std::ifstream& input);
}