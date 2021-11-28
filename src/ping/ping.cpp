#include "ping.hpp"

namespace ping
{

    /**
     * given a hostname, get a sendto() compatible sockaddr
     *
     * @param hostname the hostname to ping
     **/
    sockaddr_in sockaddr_from_hostname(std::string hostname, int port)
    {
        if (hostname == "localhost")
        {
            hostname = "127.0.0.1";
        }

        sockaddr_in addr;

        addr.sin_family = AF_INET;

        addr.sin_port = htons(port);

        inet_pton(AF_INET, hostname.c_str(), &addr.sin_addr);

        //addr.sin_addr.s_addr = inet_addr(hostname.c_str());

        return addr;
    }

    /**
     * socket_icmp but autofill port
     * 
     * @param hostname the hostname to ping 
     **/
    int socket_icmp(const std::string hostname)
    {
        return socket_icmp(hostname, 80);
    }

    /**
     * See if the server is up.
     * ICMP didn't work and required SOCK_RAW,
     * so using errno works fine enough
     *
     * @param hostname the hostname to ping
     * @param port the port to ping
     **/
    int socket_icmp(const std::string hostname, const int port)
    {
        // It's called pingu not because it's gonna ping you, but because of little penguin

        // Socket descriptor or -1
        int pingu = socket(AF_INET, SOCK_STREAM, 0);

        if (pingu < 0)
        {
            return ICMP_NO_PERMS;
        }

        sockaddr_in addr = sockaddr_from_hostname(hostname, port);

        int connection_status = connect(pingu, (sockaddr *)&addr, sizeof(addr));

        if (connection_status != -1)
        {
            // This isn't awesome, let's be honest
            return ICMP_SUCCESS | ICMP_PORT_OPEN;
        }

        // I'm still not super stoked about this line
        switch (errno)
        {
        case 111:
        {
            return ICMP_SUCCESS;
        }

        case 113:
        {
            return 4;
        }

        default:
        {
            return ICMP_FAILED;
        }
        }
    }

    /**
     * Ping a single port
     *  @param url the url to ping
     *  @param port the port to ping
     **/
    bool ping_port(const std::string url, const int port)
    {
        return socket_icmp(url, port) & ICMP_PORT_OPEN;
    }

    /**
     * Ping a vector of points, return the result as a map
     *
     * @param url the url to ping
     * @param ports pointer to ping::portlist (std::vector) of ports
     **/
    std::map<int, bool> ping_ports(std::string url, std::vector<int> *ports)
    {
        std::map<int, bool> portmap;

        for (int port : *ports)
        {
            // portmap[port] = ping_port(url, port);

            portmap.insert(std::pair<int, bool>(port, ping_port(url, port)));
        }

        return portmap;
    }

    /**
     * I may be stupid
     **/
    std::vector<int> create_ports(void)
    {
        std::vector<int> v;

        return v;
    }

    void add_port(std::vector<int> *ports, int new_port)
    {
        ports->push_back(new_port);
    }
}