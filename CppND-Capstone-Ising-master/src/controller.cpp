#include "controller.h"

Controller::Controller() : state{false, false, true, false} {
    // Possible lattice size
    nsize[0] = 10;
    nsize[1] = 20;
    nsize[2] = 50;
    nsize[3] = 100;
    nsize[4] = 200;
    nsize[5] = 500;
    nsize[6] = 1000;
}

void Controller::HandleInput(bool &running, Ising2D &ising, int &skip_frame) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:      // Increase lattice size
                    state.change_size = true;
                    (size_ind >= 6) ? size_ind = 6 : size_ind++;
                    std::cout << "Changing lattice size: " << ising.get_nrow() << "x" << ising.get_ncol() << "\n";
                    ising.resize(nsize[size_ind], nsize[size_ind]);
                    break;

                case SDLK_DOWN:    // Decrease lattice size
                    state.change_size = true;
                    (size_ind <= 0) ? size_ind = 0 : size_ind--;
                    std::cout << "Changing lattice size: " << ising.get_nrow() << "x" << ising.get_ncol() << "\n";
                    ising.resize(nsize[size_ind], nsize[size_ind]);
                    break;

                case SDLK_LEFT:    // Decrease frame skip
                    skip_frame -= 10;
                    if (skip_frame < 1) {
                        skip_frame = 1;
                    }
                    std::cout << "Decreasing frame skip to " << skip_frame << "\n";
                    break;

                case SDLK_RIGHT:   // Increase frame skip
                    skip_frame += 10;
                    if (skip_frame % 10 == 1) {
                        skip_frame -= 1;
                    }
                    if (skip_frame > 100) {
                        skip_frame = 100;
                    }
                    std::cout << "Increasing frame skip to " << skip_frame << "\n";
                    break;

                case SDLK_h:       // increase temperature
                    ising.increase_temp();
                    std::cout << "Increasing temperature to " << std::fixed << std::setprecision(1) << ising.get_temp() << "\n";
                    break;

                case SDLK_c:       // decrease temperature
                    ising.decrease_temp();
                    std::cout << "Decreasing temperature to " << std::fixed << std::setprecision(1) << ising.get_temp() << "\n";
                    break;

                case SDLK_p:       // increase initial spin probability
                    ising.increase_prob();
                    std::cout << "Increasing initial probability to " << std::fixed << std::setprecision(1) << ising.get_prob() << "\n";
                    state.reset = true;
                    break;

                case SDLK_o:       // decrease initial spin probability
                    ising.decrease_prob();
                    std::cout << "Increasing initial probability to " << std::fixed << std::setprecision(1) << ising.get_prob() << "\n";
                    state.reset = true;
                    break;

                case SDLK_s:
                    std::cout << "Results saved\n";
                    state.save = true;
                    break;

                case SDLK_SPACE:   // Pause simulation
                    state.pause = !state.pause;
                    if (state.pause) {
                        std::cout << "Simulation paused" << "\n";
                    } else {
                        std::cout << "Simulation running\n";
                    }
                    break;

                case SDLK_r:       // Reset simulation
                    state.reset = true;
                    std::cout << "Resetting lattice" << "\n";
                    break;

                case SDLK_ESCAPE:  // Quit simulation
                    running = false;
                    std::cout << "Exiting the simulation\n";
                    break;
            }
        }
    }
}