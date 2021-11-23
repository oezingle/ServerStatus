#ifndef PING_H
#define PING_H

#include <curl/curl.h>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

// most socket utils
#include <sys/socket.h>

// Socket address structs
#include <sys/types.h>

// hostname -> ip stuff
#include <arpa/inet.h>

#define ICMP_ECHO_PACKET_SIZE 64

namespace ping
{
    typedef std::vector<int> portlist;

    CURLcode perform_curl(std::string url, int port);

    bool ping_port(std::string url, int port);

    int socket_icmp(const std::string hostname);
    
    int socket_icmp(const std::string hostname, const int port);

    enum icmp_status
    {
        ICMP_NO_PERMS = 0,
        ICMP_SUCCESS,
        ICMP_FAILED
    };

    std::map<int, bool> ping_ports(std::string url, std::vector<int> *ports);

    std::vector<int> create_ports(void);

    void add_port(std::vector<int> ports, int new_port);

    void add_port(std::vector<int>* ports, int new_port);
}
#endif