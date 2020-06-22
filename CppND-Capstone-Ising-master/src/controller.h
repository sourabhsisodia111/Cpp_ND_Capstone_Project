#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <iomanip>
#include "ising.h"
#include "SDL.h"
#include "array.h"

/* States based on user input */
struct InputState {
    bool change_size;
    bool reset;
    bool pause;
    bool save;
};

class Controller {
public:
    Controller();
    void HandleInput(bool &running, Ising2D &ising, int &skip_frame);
    InputState state;

private:
    // Variable for choosing lattice size
    int size_ind = 3;
    int nsize[7];
};

#endif //CONTROLLER_H
