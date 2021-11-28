#include "output.hpp"

void output::setdisplay(int(* new_display)(vector<Server*>* servers)) {
    output::_display = new_display;
}

int output::display(vector<Server*> servers) {
    if (output::_display == nullptr) {
        cout << "No display fn set\n";

        throw std::exception();
    }

    return (*output::_display)(&servers);
}