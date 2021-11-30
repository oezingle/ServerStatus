#ifndef SERVER_LIST_HPP
#define SERVER_LIST_HPP

#include "Server.hpp"
#include "../config.hpp"

#include <future>
#include <list>

/**
 * A class that holds a std::vector of Server*'s,
 * so that the destructor can free the pointers properly
 **/
class ServerList
{
public:
    //ServerList();
    ~ServerList();

    void add(Server *server);

    std::vector<Server *> *get_list_ptr();
    std::vector<Server *> get_list();

    void ping_all();
    
private:
    std::vector<Server *> list;
};

#endif