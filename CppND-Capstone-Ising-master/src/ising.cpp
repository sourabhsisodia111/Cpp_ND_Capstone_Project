#include "ising.h"

/* Constructor */
Ising2D::Ising2D(const int &nrow, const int &ncol)
        : nrow(nrow), ncol(ncol), area(nrow * ncol),
          engine(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
          rand_col(0, static_cast<int>(ncol - 1)),
          rand_row(0, static_cast<int>(nrow - 1)),
          dice(0, static_cast<double>(1)) {

    // Default values
    prob = 0.5;
    kT = 1;

    init_lattice();
    init_spins();
}

/* Destructor */
Ising2D::~Ising2D() {
    lattice.reset();
}

/* Initialize 2D lattice */
void Ising2D::init_lattice() {
    lattice.set_size(nrow, ncol);
}

/* Initialize random spins */
void Ising2D::init_spins() {
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            (dice(engine) > prob) ? lattice(i, j) = 1 : lattice(i, j) = -1;
        }
    }
}

void Ising2D::resize(int &width, int &height) {
    /* Resize lattice and re-init spins */
    nrow = width;
    ncol = height;
    area = width * height;
    lattice.reset();
    init_lattice();
    reset();
}

void Ising2D::reset() {
    /* Resets RNG variables and re-initializes spins*/
    rand_col = std::uniform_int_distribution<int>(0, static_cast<int>(ncol - 1));
    rand_row = std::uniform_int_distribution<int>(0, static_cast<int>(nrow - 1));
    dice.reset();
    init_spins();
}

/* PBC check */
int Ising2D::pbc(int index, int Length) {
    if (index < 0) {
        return Length - 1;
    } else if (index == Length) {
        return 0;
    }
    return index;
}

/* Get total sum of nearest-neighbours */
int Ising2D::get_neighbor_sum() {
    return lattice(pbc(I + 1, nrow), J)
           + lattice(pbc(I - 1, nrow), J)
           + lattice(I, pbc(J + 1, ncol))
           + lattice(I, pbc(J - 1, ncol));
}

/* Get total energy of system */
float Ising2D::get_total_energy() {
    TotalE = 0.0;
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            TotalE += static_cast<float>(get_neighbor_sum()) * lattice(i, j);
        }
    }
    return TotalE / 2.0 / area;
}

/* Get total magnetism of system */
float Ising2D::get_total_spin() {
    TotalM = 0.0;
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            TotalM += lattice(i, j);
        }
    }
    return TotalM / area;
}

/* Generate random site in cell */
void Ising2D::pick_random_site() {
    I = rand_row(engine);
    J = rand_col(engine);
}

/* Calculate change in energy */
void Ising2D::calculate_energy() {
    dE = 2 * lattice(I, J) * get_neighbor_sum();
}

/* Flip spin */
void Ising2D::flip_spin() {
    // Flip spin
    (lattice(I, J) == 1) ? lattice(I, J) = -1 : lattice(I, J) = 1;

    // Update energy and magnet
    Mn += static_cast<float>(-2) * lattice(I, J);
    En += static_cast<float>(dE);
}

/* Sweep across lattice */
void Ising2D::sweep() {
    for (int i = 0; i < area; i++) {
        pick_random_site();
        calculate_energy();
        if (dE < 0) {
            flip_spin();
        } else {
            if (dice(engine) < std::exp(-static_cast<float>(dE) / kT)) {
                flip_spin();
            }
        }
    }
}

bool Ising2D::finish() {
    /* Check if system is converged */
    float total_spin = get_total_spin();
    return total_spin == 1.0 || total_spin == -1.0;
}

void Ising2D::increase_temp() {
    kT += 0.1;
    if (kT > 3.0) {
        kT = 3.0;
    }
}

void Ising2D::decrease_temp() {
    kT -= 0.1;
    if (kT < 0.1) {
        kT = 0.1;
    }
}

void Ising2D::increase_prob() {
    prob += 0.1;
    if (prob > 0.9) {
        prob = 0.9;
    }
}

void Ising2D::decrease_prob() {
    prob -= 0.1;
    if (prob < 0.1) {
        prob = 0.1;
    }
}
