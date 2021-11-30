#ifndef SERVER_HPP
#define SERVER_HPP

#include "ping.hpp"

class Server {
    public:
        Server(const std::string hostname, std::vector<int>* ports);

        Server(const std::string hostname, const std::string alias, std::vector<int>* ports);

        void ping();
        
        std::vector<int>* ports;
        std::map<int, bool> open_ports;
        bool is_up;
        std::string hostname;
        std::string alias;
};

#endif