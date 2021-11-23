#ifndef MAIN_H
    #define MAIN_H

    #include "ping/ping.hpp"
    #include "ping/Server.hpp"

    void ping_it(const std::string url, ping::portlist* ports);

    int main(void);
#endif