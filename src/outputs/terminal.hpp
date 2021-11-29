#ifndef OUT_TERM_HPP
#define OUT_TERM_HPP

// TODO more generic UNIX flag?
#ifdef __linux__

#define TERMINAL_RESET  printf("\e[0m")

#define TERMINAL_BOLD   printf("\e[1m")

#define TERMINAL_RED    printf("\e[31m")
#define TERMINAL_GREEN  printf("\e[32m")

#define TERMINAL_COLORS

//#elif _WIN32
// TODO terminal colors on windows
#else
#define TERMINAL_RESET
#define TERMINAL_BOLD
#define TERMINAL_RED
#define TERMINAL_GREEN

#warning "Terminal colors have not been implemented for your system"
#endif

#include "../ping/Server.hpp"
#include "../config.hpp"

namespace terminal
{
    int display(std::vector<Server *> *servers);

    uint16_t digits(int num);

    void print_with_spaces(const std::string str, int spaces);
}

#endif