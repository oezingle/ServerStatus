#ifndef PING_H
#define PING_H

#include <iostream>
#include <map>
#include <vector>

// most socket utils
#include <sys/socket.h>

// Socket address structs
#include <sys/types.h>

// hostname -> ip stuff
#include <arpa/inet.h>

namespace ping
{
    inline uint timeout_ms;

    typedef std::vector<int> portlist;

    bool ping_port(std::string url, int port);

    bool socket_icmp_bool(const std::string hostname);

    int socket_icmp(const std::string hostname, const int port = 80);

    // I wanted to switch to #defines, but it breaks
    enum icmp_status
    {
        ICMP_NO_PERMS = 0b000,
        ICMP_SUCCESS = 0b011,
        ICMP_FAILED = 0b010,
        ICMP_PORT_OPEN = 0b100
    };

    std::map<int, bool> ping_ports(std::string url, std::vector<int> *ports);
}
#endif