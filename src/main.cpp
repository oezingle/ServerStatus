#include "main.hpp"

using namespace std;

int main(void)
{
    ping::portlist ports = ping::create_ports();

    ping::add_port(&ports, 22);
    ping::add_port(&ports, 80);
    ping::add_port(&ports, 443);
    ping::add_port(&ports, 8000);

    Server* serv = new Server("localhost", &ports);
    
    //serv->print();

    delete serv;
    
    //ping_it("localhost", &ports);
    
    return 0;
}

void ping_it(const std::string url, ping::portlist* ports)
{
    int server_status = ping::socket_icmp(url);

    if (server_status == ping::ICMP_FAILED) {
        cout << "server " + url + " is down" << '\n';

        return;
    }

    map<int, bool> open_ports = ping::ping_ports(url, ports);

    cout << "ports on host " << url << '\n';
    for (const auto &kv : open_ports)
    {
        const int key = kv.first;
        const bool value = kv.second;

        cout << key << ": " << (value ? "open" : "closed") << '\n';
    }
}