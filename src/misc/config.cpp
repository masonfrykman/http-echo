#include "config.hpp"

#include "utils.hpp"

void he::config::loadFromFile(std::ifstream input) {
    std::string line;
    while(getline(std::cin, line)) {
        if(line.empty()) continue;
        if(line.at(line.length() - 1) == '\n') {
            // strip newline
            line.pop_back();
        }
        
        util::trimLeft(line);
        if(line.empty()) continue;

        // check for comments (# and //)
        if(line.at(0) == '#' || (line.length() > 1 && line.at(0) == '/' && line.at(1) == '/')) continue;

        // add kv pair
        size_t firstWs = line.find_first_of(' ');
        if(firstWs == std::string::npos || firstWs == line.length() - 1) continue;
        
        store[line.substr(0, firstWs)] = line.substr(firstWs + 1);
    }
}