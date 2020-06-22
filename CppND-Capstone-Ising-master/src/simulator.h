#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

#include "ising.h"
#include "array.h"
#include "renderer.h"
#include "controller.h"

class Simulator {
public:
    Simulator(int &nrow, int &ncol);
    void Run(Controller &controller, Renderer &renderer);

private:
    Ising2D ising;
    int step;

    Array1D<int> tStep;
    Array1D<float> Temperature;
    Array1D<float> Energy;
    Array1D<float> Spin;

    void print_info();
    void write_results(const std::string &filename);
};

#endif //SIMULATOR_H
