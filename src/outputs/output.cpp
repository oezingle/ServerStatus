#include "output.hpp"

/**
 * Set the function pointer for displaying ping data
 * 
 * @param new_display the function to use
 **/
void output::setdisplay(int(* new_display)(vector<Server*>*)) {
    output::_display = new_display;
}

/**
 * Ping and display the servers
 * 
 * @param servers a pointer to the lst of servers
 **/
int output::display(vector<Server*>* servers) {
    if (output::_display == nullptr) {
        cout << "No display fn set\n";

        // TODO custom exception for no display fn pointer
        throw std::exception();
    }

    return output::_display(servers);
}