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

#define PING_PORTLIST std::vector<int>

namespace ping
{
    CURLcode perform_curl(std::string url, int port);

    bool ping_port(std::string url, int port);

    std::map<int, bool> ping_ports(std::string url, std::vector<int> *ports);

    std::vector<int> create_ports(void);

    void add_port(std::vector<int> ports, int new_port);

    void add_port(std::vector<int>* ports, int new_port);
}
#endif