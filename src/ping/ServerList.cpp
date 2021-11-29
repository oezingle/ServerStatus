#include "ServerList.hpp"

// This file really doesn't need to exist, but I wanted main.cpp to be super clean

/**
 * Destructor to delete pointed values
 **/
ServerList::~ServerList() {
    for (Server* server : this->list) {
        delete server;
    }
}

/**
 * Add to the list.
 **/
void ServerList::add(Server* server) {
    this->list.push_back(server);
}

/**
 * Get the address of the server list
 **/
std::vector<Server*>* ServerList::getListPtr() {
    // Ignore the ugliness of this line, it's the only 
    //way VS code doesn't complain
    return &(this->list);
}

/**
 * Get the server list
 **/
std::vector<Server*> ServerList::getList() {
    // Ignore the ugliness of this line, it's the only 
    //way VS code doesn't complain
    return this->list;
}