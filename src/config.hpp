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

#include "json/config.h"
#include "json/ports.h"

#define CONFIG_DIR std::string("config")

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

    std::vector<std::string> get_hosts();

    std::vector<int> get_ports();

    std::string get_description(int port);
}

#endif