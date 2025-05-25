#pragma once

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
        return ""
    }
}