#include "Server.hpp"

/**
 * A class that holds a std::vector of Server*'s,
 * so that the destructor can free the pointers properly
 **/
class ServerList {
    public:
        //ServerList();
        ~ServerList();

        void add(Server* server);

        std::vector<Server*>* getListPtr();
        std::vector<Server*> getList();

    private:
        std::vector<Server*> list;
};