#include "main.hpp"

using namespace std;

int main (void) {
    PING_PORTLIST ports = ping::create_ports();
    
    ping::add_port(&ports, 22);
    ping::add_port(&ports, 80);
    ping::add_port(&ports, 443);

    string url = "localhost";

    map<int, bool> open_ports = ping::ping_ports(url, &ports);

    cout << "ports on host " << url << '\n';
    for (const auto& kv : open_ports) {
        const int key = kv.first;
        const bool value = kv.second;
        
        cout << key << ": " << (value ? "open" : "closed") << '\n';
    }

    return 0;
}