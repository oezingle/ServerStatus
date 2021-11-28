#include "main.hpp"

using namespace std;

int main(void)
{
    ping::portlist ports = ping::create_ports();

    ping::add_port(&ports, 22);
    ping::add_port(&ports, 80);
    ping::add_port(&ports, 443);
    ping::add_port(&ports, 8000);

    ServerList server_list;

    server_list.add(new Server("localhost", &ports));

    terminal::display(server_list.getListPtr());
    
    return 0;
}