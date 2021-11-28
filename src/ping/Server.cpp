#include "Server.hpp"

using namespace std;

Server::Server(const string hostname, ping::portlist* ports)
{
    this->hostname = hostname;

    this->is_up = ping::socket_icmp(hostname);

    this->open_ports = ping::ping_ports(hostname, ports);
}
