#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace he::http {
    class Response {
    private:
        int status;
        std::unordered_map<std::string, std::string> headers;
        std::string body;

    public:
        Response(int status, std::string body) : status(status), body(body) {}

        // Getters
        int status() { return status; }
        std::unordered_map<std::string, std::string> headers() { return headers; }
        std::string body() { return body; }

        // Setters
        void setStatus(int newVal) { status = newVal; }
        void setBody(std::string newBody) { body = newBody; }

        void setHeader(std::string key, std::string value) {
            if(key.empty()) throw std::invalid_argument("Key cannot be empty.");
            if(key == "Content-Length") throw std::invalid_argument("The Content-Length header is managed by the class.");
            
            headers[key] = value;
        }

        // More header stuff
        bool containsHeader(std::string key) { return headers.count(key) == 0; }
        void removeHeader(std::string key) { headers.erase(key); }

        // Synthesis

        // Converts a status code to it's reason phrase as in RFC 2616
        static std::string reasonPhrase(int status) {
            switch(status) {
                case 100: return "Continue";
                case 101: return "Switching Protocols";
                case 200: return "OK";
                case 201: return "Created";
                case 202: return "Accepted";
                case 203: return "Non-Authoritative Information";
                case 204: return "No Content";
                case 205: return "Reset Content";
                case 206: return "Partial Content";
                case 300: return "Multiple Choices";
                case 301: return "Moved Permanently";
                case 302: return "Found";
                case 303: return "See Other";
                case 304: return "Not Modified";
                case 305: return "Use Proxy";
                case 307: return "Temporary Redirect";
                case 400: return "Bad Request";
                case 401: return "Unauthorized";
                case 402: return "Payment Required";
                case 403: return "Forbidden";
                case 404: return "Not Found";
                case 405: return "Method Not Allowed";
                case 406: return "Not Acceptable";
                case 407: return "Proxy Authentication Required";
                case 408: return "Request Timeout";
                case 409: return "Conflict";
                case 410: return "Gone";
                case 411: return "Length Required";
                case 412: return "Precondition Failed";
                case 413: return "Request Entity Too Large";
                case 414: return "Request-URI Too Long";
                case 415: return "Unsupported Media Type";
                case 416: return "Requested Range Not Satisfiable";
                case 417: return "Expectation Failed";
                case 500: return "Internal Server Error";
                case 501: return "Not Implemented";
                case 502: return "Bad Gateway";
                case 503: return "Service Unavailable";
                case 504: return "Gateway Timeout";
                case 505: return "HTTP Version Not Supported";
            }
            throw std::invalid_argument("Status code " + std::to_string(status) + " does not correspond to a valid reason phrase.");
        }

        std::string heading() {
            std::stringstream out("HTTP/1.1 ");

            out << status << " " << reasonPhrase(status) << std::endl;

            // On-the-fly Content-Length
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