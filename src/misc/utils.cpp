#include "utils.hpp"

void he::util::trimRight(std::string& str) {
    if(str.empty()) return;
    for(auto it = str.end() - 1; (it != --str.begin() && isblank(*it)); it++) str.erase(it);
}

void he::util::trimLeft(std::string& str) {
    if(str.empty()) return;
    for(auto it = str.begin(); (it != str.end() && isblank(*it)); it++) str.erase(it);
}