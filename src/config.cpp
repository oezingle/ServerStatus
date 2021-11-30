#include "config.hpp"

using namespace std;

namespace json = boost::json;

/*
 * "description": true means use default
 * check if keys are alphabetized
 */

/**
 * Create default configuration files, if needed
 **/
void config::defaults()
{
    config::filename = std::string(CONFIG_DIR) + separator() + std::string("config.json");

    struct stat info;

    if (stat(CONFIG_DIR, &info) != 0)
    {
        // Create a new directory
        // requires C++17, consider a more historically minded option
        filesystem::create_directory(CONFIG_DIR);
    }
    else if ((!info.st_mode & S_IFDIR) && (!info.st_mode & S_IFLNK))
    {
        // TODO follow symlinks, check if that is a directory

        cerr << CONFIG_DIR << " exists but is not a directory\n";

        // TODO custom file exists but isn't a directory exception
        throw exception();
    }

    if (stat(filename.c_str(), &info) != 0)
    {
        std::ofstream out(filename);

        out << config_default;

        out.close();
    }
}

/**
 * Parse the configuration into JSON
 **/
void config::load()
{
    // ! TODO this breaks everything
    /*if (config::_json.size() == 0) {
        // Config has already loaded, why bother?
        return;
    }*/

    json::stream_parser parser;

    char ch;
    fstream fin(filename, fstream::in);
    while (fin >> noskipws >> ch)
    {
        // cout << ch; // Or whatever

        parser.write(string(&ch));
    }

    assert(parser.done());

    json::value json_value = parser.release();

    config::_json = json_value.as_object();

    insert_descriptions();
}

/**
 * Populate the config::_descriptions map
 **/
void config::insert_descriptions()
{
    // Why waste memory?
    if (!use_descriptions())
    {
        return;
    }

    // TODO this should use boost's partial json parser, to work in chunks
    json::array default_descriptions = json::parse((char *)port_defaults).as_array();

    for (json::value item : default_descriptions)
    {
        json::object obj = item.as_object();

        config::_descriptions.emplace(
            (int)obj.at("port").as_int64(),
            string(obj.at("description").as_string().c_str()));
    }

    // Load up user defined ports (config.json) and see what's up
    json::array user_ports = _json.at("ports").as_array();

    for (uint16_t index = 0; index < user_ports.size(); index++)
    {
        json::object index_object = user_ports.at(index).as_object();

        if (index_object.find("description") == index_object.end())
            continue;

        int port = index_object.at("port").as_int64();
        json::string description = index_object.at("description").as_string();

        config::_descriptions.emplace(port, string(description.c_str()));
    }
}

/**
 * Does the user even want to see descriptions for their ports?
 **/
bool config::use_descriptions()
{
    if (_json.find("descriptions") == _json.end())
    {
        // The user hasn't set a value for this key
        return true;
    }
    return _json.at("descriptions").as_bool();
}

/**
 * Allow async/threading?
 **/
bool config::use_async()
{
    if (_json.find("async") == _json.end())
    {
        // The user hasn't set a value for this key
        return false;
    }
    return config::_json.at("async").as_bool();
}

/**
 * Get the timeout for sockets.
 **/
void config::set_timeout(uint *ptr)
{
    uint timeout = 0;

    if (_json.find("timeout") == _json.end())
    {
        timeout = 1000;
    }
    else
    {
        timeout = _json.at("timeout").as_int64();
    }

    *ptr = timeout;
}

/**
 * Get the configured list of hostnames
 **/
vector<string> config::get_hosts()
{
    json::array server_array = config::_json.at("servers").as_array();

    vector<string> server_vector;

    for (auto item : server_array)
    {
        server_vector.push_back(item.as_string().c_str());
    }

    return server_vector;
}

/**
 * Get the configured servers as a ServerList
 **/
ServerList config::get_servers(vector<int> *ports)
{
    ServerList server_list;

    json::array server_array = config::_json.at("servers").as_array();

    for (json::value item : server_array)
    {
        if (item.is_string())
        {
            json::string tmp_hostname = item.as_string();

            string hostname(tmp_hostname.begin(), tmp_hostname.end());

            server_list.add(new Server(hostname, ports));
        }
        else if (item.is_object())
        {
            json::object dict = item.as_object();

            json::string tmp_hostname = dict.at("hostname").as_string();
            json::string tmp_alias = dict.at("alias").as_string();

            string hostname(tmp_hostname.begin(), tmp_hostname.end());
            string alias(tmp_alias.begin(), tmp_alias.end());

            server_list.add(new Server(hostname, alias, ports));
        }
        else
        {
            throw json::error();
        }
    }

    return server_list;
}

/**
 * Get the configured port list
 **/
vector<int> config::get_ports()
{
    vector<int> nums;

    json::array ports_array = config::_json.at("ports").as_array();

    for (uint16_t index = 0; index < ports_array.size(); index++)
    {
        json::object index_object = ports_array.at(index).as_object();

        int port = index_object.at("port").as_int64();

        // TODO binary search & sort in place should be faster than std::sort

        nums.push_back(port);
    }

    sort(nums.begin(), nums.end());

    return nums;
}

/**
 * Get a description for a given port
 * 
 * @param port the port number to describe
 **/
std::string config::get_description(int port)
{
    if (_descriptions.find(port) != _descriptions.end())
    {
        return _descriptions.at(port);
    }
    else
    {
        return "?";
    }
}