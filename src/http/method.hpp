#pragma once

#include <stdexcept>
#include <string>

namespace he::http {
    enum Method {
        GET, HEAD, POST, DELETE, PUT, OPTIONS
    };

    std::string methodToString(Method method) noexcept {
        switch(method) {
            case GET: return "GET";
            case HEAD: return "HEAD";
            case POST: return "POST";
            case DELETE: return "DELETE";
            case PUT: return "PUT";
            case OPTIONS: return "OPTIONS";
        }
        return "";
    }

    Method stringToMethod(std::string str) {
        if(str == "GET") return GET;
        else if(str == "HEAD") return HEAD;
        else if(str == "POST") return POST;
        else if(str == "DELETE") return DELETE;
        else if(str == "PUT") return PUT;
        else if(str == "OPTIONS") return OPTIONS;
        
        throw std::invalid_argument("str is not a valid method.");
    }
}