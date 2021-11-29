#ifndef OUT_OUTPUT_HPP
#define OUT_OUTPUT_HPP

#include "../ping/Server.hpp"

using namespace std;

namespace output {
    // Variable for function pointer of display method
    inline int (* _display)(vector<Server*>*) = nullptr;

    int display(vector<Server*>* servers);

    void setdisplay(int(* new_display)(vector<Server*>* servers));
}

#endif