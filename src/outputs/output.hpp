#ifndef OUT_OUTPUT_HPP
#define OUT_OUTPUT_HPP

#include "../ping/Server.hpp"

using namespace std;

namespace output {
    // Variable for function pointer to display method
    int(* _display)(vector<Server*>* servers);

    int display(vector<Server*> servers);

    void setdisplay(int(* new_display)(vector<Server*>* servers));
}

#endif