#include "main.hpp"

using namespace std;

int main(void)
{
    config::defaults();
    
    config::load();

    vector<int> ports = config::get_ports();

    ServerList server_list;

    for (const string hostname : config::get_hosts())
    {
        server_list.add(new Server(hostname, &ports));
    }

    output::setdisplay(terminal::display);

    output::display(server_list.getListPtr());

    return 0;
}