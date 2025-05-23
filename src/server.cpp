#include <fstream>
#include <iostream>

#include "misc/config.hpp"

int main(int argc, char const *argv[])
{
    // load configs
    std::ifstream cfgFd("/etc/http-echo.cfg");
    if(!cfgFd.good()) {
        std::cerr << "Failed to open /etc/http-echo.cfg for reading." << std::endl;
        return 1;
    }

    he::config::loadFromFile(cfgFd);
    cfgFd.close();

    if(he::config::store.count("Address") == 0 || he::config::store.count("Port") == 0) {
        std::cerr << "Config file must contain Address and Port values to start.";
        return 1;
    }

    

    return 0;
}