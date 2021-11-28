#include "ServerList.hpp"

ServerList::~ServerList() {
    for (Server* server : this->list) {
        delete server;
    }
}

void ServerList::add(Server* server) {
    this->list.push_back(server);
}

std::vector<Server*>* ServerList::getListPtr() {
    // Ignore the ugliness of this line, it's the only 
    //way VS code doesn't complain
    return &(this->list);
}

std::vector<Server*> ServerList::getList() {
    // Ignore the ugliness of this line, it's the only 
    //way VS code doesn't complain
    return this->list;
}