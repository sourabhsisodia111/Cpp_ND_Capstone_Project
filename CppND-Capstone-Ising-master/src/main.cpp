#include "simulator.h"
#include "renderer.h"
#include "controller.h"

int main() {
    /* Window size */
    constexpr std::size_t kScreenWidth{480};
    constexpr std::size_t kScreenHeight{480};

    // Initial lattice size
    int Row = 100;
    int Col = 100;

    /* Create instances */
    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;
    Simulator sim(Row, Col);

    /* Run simulation */
    sim.Run(controller, renderer);

    return 0;
}
