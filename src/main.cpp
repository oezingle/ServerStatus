#include "main.hpp"

using namespace std;

int main(void)
{
    config::defaults();
    
    // Load the configuration
    config::load();

    // Set the timeout variable
    config::set_timeout(&ping::timeout_ms);

    // Grab the ports
    vector<int> ports = config::get_ports();

    // Create Servers
    ServerList server_list = config::get_servers(&ports);

    server_list.ping_all();

    output::setdisplay(terminal::display);

    output::display(server_list.get_list_ptr());

    return 0;
}