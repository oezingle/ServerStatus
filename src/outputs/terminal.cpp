#include "terminal.hpp"

using namespace std;
using namespace terminal;

/**
 * Ping servers and display their information
 * 
 * @param servers pointer to a list of servers
 * 
 * @returns 0. nothing ever goes wrong. /s
 **/
int terminal::display(vector<Server *> *servers)
{
    // Display the header
    uint16_t max_hostname_length = 0;

    for (Server *server : *servers)
    {
        uint16_t len = server->alias.length();

        if (len > max_hostname_length)
        {
            max_hostname_length = len;
        }
    }

    max_hostname_length++;

    TERMINAL_BOLD;

    print_with_spaces(string("Hostname"), max_hostname_length);

    cout << "Up ";

    for (const auto port : *servers->at(0)->ports)
    {
        cout << port << " ";
    }

    TERMINAL_RESET;

    cout << "\n";

    // Print info for every server
    for (Server *server : *servers)
    {
        // cout << server->hostname;

        print_with_spaces(server->alias, max_hostname_length);

        //server->ping();

#ifdef TERMINAL_COLORS
        if (server->is_up)
        {
            TERMINAL_GREEN;
        }
        else
        {
            TERMINAL_RED;
        }

        cout << "o";

        TERMINAL_RESET;
#else
        if (server->is_up)
        {
            cout << "X";
        }
        else
        {
            cout << "-";
        }
#endif

        cout << "  ";

        for (const auto &kv : server->open_ports)
        {
            const int port = kv.first;

            const bool status = kv.second;

#ifdef TERMINAL_COLORS
            if (status)
            {
                TERMINAL_GREEN;
            }
            else
            {
                TERMINAL_RED;
            }

            print_with_spaces("o", digits(port) + 1);

            TERMINAL_RESET;
#else
            if (server->is_up)
            {
                print_with_spaces("X", digits(port) + 1);
            }
            else
            {
                print_with_spaces("-", digits(port) + 1);
            }
#endif
        }

        TERMINAL_RESET;

        cout << "\n";
    }

    if (config::use_descriptions())
    {
        TERMINAL_BOLD;

        cout << "\nPort  Description\n";

        TERMINAL_RESET;

        for (const auto port : *servers->at(0)->ports)
        {
            print_with_spaces(to_string(port), 6);

            cout << config::get_description(port) << "\n";
        }
    }

    return 0;
}

/**
 * Count how many digits there are in a number
 *
 * @param num the number to count digits
 *
 * @returns the number of digits in that number (dec)
 **/
uint16_t terminal::digits(int num)
{
    uint16_t length = 1;

    while (num /= 10)
        length++;

    return length;
}

/**
 * Print a string with space padding on the right.
 * Does not support unicode. If the string is longer than
 * spaces, it will run over.
 *
 * @param str the string to print
 * @param spaces the width in total
 *
 **/
void terminal::print_with_spaces(const string str, int spaces)
{
    cout << str;

    int index = 0;

    for (index = str.length(); index < spaces; index++)
    {
        cout << " ";
    }
}