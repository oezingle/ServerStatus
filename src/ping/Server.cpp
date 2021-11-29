#include "Server.hpp"

using namespace std;

/**
 * Server constructor
 * 
 * @param hostname the string hostname
 * @param ports a std::vector of ports to ping
 **/
Server::Server(const string hostname, ping::portlist *ports)
{
    this->hostname = hostname;

    this->ports = ports;
}

/**
 * Ping a server, and all its ports. 
 * If the initial ICMP ping fails, all others 
 * are marked as failed for speed
 **/
void Server::ping()
{
    this->is_up = ping::socket_icmp_bool(hostname);

    if (this->is_up)
    {
        this->open_ports = ping::ping_ports(hostname, this->ports);
    }
    else
    {
        // The server's first ping said down, so we fill with falses
        for (int port : *this->ports)
        {
            this->open_ports.insert(pair(port, false));
        }
    }
}
