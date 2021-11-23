#include "output.hpp"

void output::setdisplay(int(* new_display)(vector<Server*> servers)) {
    output::_display = new_display;
}

int output::display(vector<Server*> servers) {
    return (*output::_display)(servers);
}