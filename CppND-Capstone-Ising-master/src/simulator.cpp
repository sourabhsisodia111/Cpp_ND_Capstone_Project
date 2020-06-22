#include "simulator.h"

Simulator::Simulator(int &nrow, int &ncol) : ising(nrow, ncol) {
    step = 0;
};

void Simulator::Run(Controller &controller, Renderer &renderer) {
    bool running = true;

    while (running) {
        // Get keyboard input
        controller.HandleInput(running, ising, renderer.skip_frame);

        /* Main */
        if (controller.state.pause) { // Pause
            renderer.Render(ising);
            renderer.UpdateWindowTitle(step, ising, controller.state);

        } else { // Normal run
            if (step % renderer.skip_frame == 0) {
                renderer.Render(ising);
                renderer.UpdateWindowTitle(step, ising, controller.state);
            }
            // Perform MMC sweep of lattice
            ising.sweep();
            step++;

            // Update results
            tStep.add_element(step);
            Energy.add_element(ising.get_total_energy());
            Spin.add_element(ising.get_total_spin());
            Temperature.add_element(ising.get_temp());

            // Pause if all spins are up or down.
            if (ising.finish()) {
                controller.state.pause = true;

            }
        }

        /* Change lattice size */
        if (controller.state.change_size) {
            renderer.Render(ising);
            renderer.UpdateWindowTitle(step, ising, controller.state);

            step = 0;
            controller.state.change_size = false;
        }

        /* Save results of current state */
        if (controller.state.save) {
            write_results("ising2d_results.txt");
            controller.state.save = false;
        }

        /* Reset simulation */
        if (controller.state.reset) {
            ising.reset();
            tStep.reset();
            Temperature.reset();
            Energy.reset();
            Spin.reset();
            step = 0;
            controller.state.reset = false;
            controller.state.pause = true;
        }
    }

    // Print final info after quiting
    print_info();
}

void Simulator::print_info() {
    std::cout << "\n";
    std::cout << "Lattice dimension  : " << ising.get_nrow() << "x" << ising.get_ncol() << "\n";
    std::cout << "Number of MC steps : " << step << "\n";
    std::cout << "Total energy       : " << std::fixed << std::setprecision(1) << ising.get_total_energy() << "\n";
    std::cout << "Total spin         : " << std::fixed << std::setprecision(1) << ising.get_total_spin() << "\n";
}

void Simulator::write_results(const std::string &filename) {
    std::ofstream ofile(filename);
    if (ofile.is_open()) {
        // Header
        ofile << "# 2D Ising model\n";
        ofile << "# --------------\n";
        ofile << "# Lattice size: " << ising.get_nrow() << "x" << ising.get_ncol() << "\n";
        ofile << "# Initial probability: " << ising.get_prob() << "\n";
        ofile << "# Number of steps: " << step << "\n";
        ofile << "#\n";
        ofile << "# Step | Temperature | Total Energy | Total Spin\n";
        for (int i = 0; i < tStep.get_size(); i++) {
            ofile << std::setw(8) << tStep(i) << "  "
                  << std::setw(6) << std::fixed << std::setprecision(1) << Temperature(i) << "  "
                  << std::setw(6) << std::fixed << std::setprecision(2) << Energy(i) << "  "
                  << std::setw(6) << std::fixed << std::setprecision(2) << Spin(i) << "\n";
        }
    }
    ofile.close();
}