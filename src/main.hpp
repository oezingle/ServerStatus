#ifndef MAIN_H
    #define MAIN_H

    #include "ping/ping.hpp"
    #include "ping/Server.hpp"
    #include "ping/ServerList.hpp"
    
    #include "outputs/output.hpp"
    #include "outputs/terminal.hpp"

    void ping_it(const std::string url, ping::portlist* ports);

    int main(void);
#endif