#include "ServerList.hpp"

using namespace std;

namespace json = boost::json;

// This file really doesn't need to exist, but I wanted main.cpp to be super clean

/**
 * Destructor to delete pointed values
 **/
ServerList::~ServerList()
{
    for (Server *server : this->list)
    {
        delete server;
    }
}

/**
 * Add to the list.
 **/
void ServerList::add(Server *server)
{
    this->list.push_back(server);
}

/**
 * Get the address of the server list
 **/
std::vector<Server *> *ServerList::get_list_ptr()
{
    // Ignore the ugliness of this line, it's the only
    //way VS code doesn't complain
    return &(this->list);
}

/**
 * Get the server list
 **/
std::vector<Server *> ServerList::get_list()
{
    // Ignore the ugliness of this line, it's the only
    //way VS code doesn't complain
    return this->list;
}

/**
 * Ping all servers asynchronously
 **/
void ServerList::ping_all()
{
    using namespace std;

    if (config::use_async())
    {
        std::list<future<void>> pings;

        for (Server *server : this->list)
        {
            pings.push_front(async(launch::async, &Server::ping, server));
        }

        std::list<future<void>>::iterator ping;
        for (ping = pings.begin(); ping != pings.end(); ++ping)
        {
            ping->wait();
        }
    }
    else
    {
        for (Server *server : this->list)
        {
            server->ping();
        }
    }
}