#ifndef ISING2D_H
#define ISING2D_H

#include <fstream>
#include <string>
#include <cmath>
#include <chrono>
#include <random>
#include <functional>

#include "array.h"

class Ising2D {
public:
    /* Constructor & Destructor */
    Ising2D(const int &nrow, const int &ncol);
    ~Ising2D();

    /* Get Methods */
    int get_ncol() const { return ncol; };
    int get_nrow() const { return nrow; };
    float get_prob() const { return prob; };
    float get_temp() const { return kT; };
    int get_element(int &i, int &j) { return lattice(i, j); };
    float get_total_energy();
    float get_total_spin();

    /* Ising methods */
    void pick_random_site();
    void calculate_energy();
    void sweep();
    void flip_spin();

    /* Controller specific methods*/
    void increase_temp();
    void decrease_temp();
    void increase_prob();
    void decrease_prob();
    void resize(int &width, int &height);
    void reset();
    bool finish();

private:
    /* Variables */
    int nrow;
    int ncol;
    float prob;
    float kT;
    int area;
    int I = 0;
    int J = 0;
    int dE = 0;
    float Mn = 0.0;
    float En = 0.0;
    float TotalE{};
    float TotalM{};

    /* RNG variables */
    std::mt19937 engine;
    std::uniform_real_distribution<double> dice;
    std::uniform_int_distribution<int> rand_col;
    std::uniform_int_distribution<int> rand_row;

    /* Lattice container */
    Array2D<int> lattice;

    /* Private methods */
    void init_lattice();
    void init_spins();
    static int pbc(int index, int Length);
    int get_neighbor_sum();
};

#endif // ISING2D_H