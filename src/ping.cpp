#include "ping.h"

// TODO ping without port can't use curl -  https://stackoverflow.com/questions/13759760/how-to-know-if-a-server-is-online-or-not-if-we-only-know-the-ip

namespace ping
{

    size_t noop_cb(void *ptr, size_t size, size_t nmemb, void *data)
    {
        return size * nmemb;
    }

    CURLcode perform_curl(const std::string url, const int port)
    {
        CURL *curl = curl_easy_init();

        if (!curl)
        {
            // TODO raise error
            throw std::bad_alloc();
        }

        // Set url, port
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_PORT, port);

        // Mute output
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        return res;
    }

    /**
     * Ping a single port
     *  @param url the url to ping
     *  @param port the port to ping
    **/
    bool ping_port(const std::string url, const int port)
    {
        return perform_curl(url, port) != CURLE_COULDNT_CONNECT;
    }

    /**
     * Ping a vector of points, return the result as a map 
    **/
    std::map<int, bool> ping_ports(std::string url, std::vector<int> *ports)
    {
        std::map<int, bool> portmap;

        for (int port : *ports)
        {
            //portmap[port] = ping_port(url, port);

            portmap.insert(std::pair<int, bool>(port, ping_port(url, port)));
        }

        return portmap;
    }

    std::vector<int> create_ports(void)
    {
        std::vector<int> v;

        return v;
    }

    void add_port(std::vector<int> *ports, int new_port)
    {
        ports->push_back(new_port);
    }
}