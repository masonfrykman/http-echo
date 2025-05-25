#include <fstream>
#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <stdexcept>

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

    auto addrStr = he::config::store.at("Address");
    auto portStr = he::config::store.at("Port");

    // Bring up the server

    struct addrinfo hint;
    struct addrinfo *bindAddress;

    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    // TODO: Error checking on the socket operations
    int lookup = getaddrinfo(addrStr.c_str(), portStr.c_str(), &hint, &bindAddress);
    if(lookup != 0) {
        throw std::runtime_error("Socket Error at getaddrinfo(): " + std::string(gai_strerror(lookup)));
    }

    int sock = socket(bindAddress->ai_protocol, SOCK_STREAM, 0);
    if(sock == -1) {
        throw std::runtime_error("Socket Error at socket(), errno: " + errno);
    }

    int bindOp = bind(sock, bindAddress->ai_addr, bindAddress->ai_addrlen);
    if(bindOp == -1) {
        throw std::runtime_error("Socket Error at bind(), errno: " + errno);
    }

    int listenOp = listen(sock, 15);
    if(listenOp == -1) {
        throw std::runtime_error("Socket Error at listen(), errno: " + errno);
    }

    while(true) {
        struct sockaddr acceptedSockaddr;
        socklen_t acceptedSocklen;

        int acceptedSocket = accept(sock, &acceptedSockaddr, &acceptedSocklen);
    }

    return 0;
}