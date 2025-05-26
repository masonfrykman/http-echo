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
        Request(std::string data) {
            if(data.empty()) throw std::invalid_argument("Data cannot be empty.");
            
            // First line
            size_t firstNewline = data.find_first_of('\n');
            if(firstNewline == std::string::npos) throw std::invalid_argument("Not a valid request.");

            std::string firstLine = data.substr(0, firstNewline);
            
            size_t firstWS = firstLine.find_first_of(' ');
            if(firstWS == std::string::npos) throw std::invalid_argument("Not a valid request.");

            std::string methodStr = data.substr(0, firstWS);
            method = stringToMethod(methodStr);

            size_t nextWS = firstLine.find_first_of(' ', firstWS + 1);
            if(nextWS == std::string::npos) throw std::invalid_argument("Not a valid request.");

            path = firstLine.substr(firstWS + 1, nextWS - firstWS - 1);

            // Headers
            std::string dataWithoutFirstline = data.substr(firstNewline + 1);

            auto it = dataWithoutFirstline.begin();
            std::string line;
            while(it != dataWithoutFirstline.end() && !(*it == '\n' && *(it++) == '\n')) {
                if(*it == '\n') { // Process the line
                    size_t delimiter = line.find_first_of(": ");
                    if(delimiter != std::string::npos && delimiter != line.size() - 2) { // Don't commit a line that is invalid.
                        headers[line.substr(0, delimiter)] = line.substr(delimiter + 1);
                    }
                    line.clear();
                    continue;
                }
                line.push_back(*it);
            }

            // Body
            if(it == dataWithoutFirstline.end()) {
                body = nullptr;
                return;
            }
            it += 2;
            while(it < dataWithoutFirstline.end()) {
                body.push_back(*it);
                it++;
            }
        }

        // First line getters
        Method getMethod() { return method; }
        std::string getPath() { return path; }
        std::string formattedFirstLine() { return methodToString(method) + " " + path + " HTTP/1.1"; }
        
        // First line setters
        void setMethod(Method newVal) { method = newVal; }
        void setPath(std::string newVal) { path = newVal; }

        // Header getters / setters
        std::unordered_map<std::string, std::string> getHeaders() { return headers; }

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