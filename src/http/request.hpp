#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "method.hpp"

namespace he::http {

    /// An HTTP/1.1 request
    class Request {
    private:
        // First line
        Method method;
        std::string path;
        
        // Headers
        std::unordered_map<std::string, std::string> headers;

        // Body
        std::string body;
    public:
        Request(Method method, std::string path, std::string body) : method(method), path(path), body(body) {}

        // First line getters
        Method method() { return method; }
        std::string path() { return path; }
        std::string formattedFirstLine() { return methodToString(method) + " " + path + " HTTP/1.1"; }
        
        // First line setters
        void setMethod(Method newVal) { method = newVal; }
        void setPath(std::string newVal) { path = newVal; }

        // Header getters / setters
        std::unordered_map<std::string, std::string> headers() { return headers; }

        void setHeader(std::string key, std::string value) {
            if(key.empty()) throw std::invalid_argument("Key cannot be empty");
            if(key == "Content-Length") throw std::invalid_argument("Content-Length is managed by the class.");
            headers[key] = value;
        }

        void removeHeader(std::string key) {
            if(key.empty() || headers.count(key) == 0) return;
            headers.erase(key);
        }

        bool containsHeader(std::string key) { return headers.count(key) == 1; }

        // Request synthesis
        std::string heading() {
            std::stringstream out;

            out << formattedFirstLine() << std::endl;

            // include Content-Length on the fly
            out << "Content-Length: " << body.length() << std::endl;

            for(auto[k,v] : headers) {
                out << k << ": " << v << std::endl;
            }

            out << std::endl;

            return out.str();
        }

        std::string toString() {
            return heading() + body;
        }
    };
}