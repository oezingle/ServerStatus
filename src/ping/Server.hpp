

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ping.hpp"

class Server {
    public:
        Server(const std::string hostname, ping::portlist* ports);

        void ping();
        
        std::vector<int>* ports;
        std::map<int, bool> open_ports;
        bool is_up;
        std::string hostname;
};

#endif