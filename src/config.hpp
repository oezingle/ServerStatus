#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/json.hpp>

// Stat files to check if defaults exist
#include <sys/stat.h>

// can be removed once I implement a custom exception
// and remove cout / cerr calls
#include <iostream>

// Write to file
#include <fstream>

// Standard(?) Filesystem utils, but requires C++17
#include <filesystem>

// xxd'd json files
#include "json/config.h"
#include "json/ports.h"

// Forward declaration
class ServerList;

#include "ping/ServerList.hpp"

#ifndef CONFIG_DIR
#define CONFIG_DIR "config"
#endif

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

namespace config
{
    inline std::string filename = "";

    inline boost::json::object _json = {};

    inline std::map<int, std::string> _descriptions = {};

    void load();

    void insert_descriptions();

    void defaults();

    bool use_descriptions();

    bool use_async();

    void set_timeout(uint *ptr);

    std::vector<std::string> get_hosts();

    ServerList get_servers(std::vector<int> *ports);

    std::vector<int> get_ports();

    std::string get_description(int port);
}

#endif