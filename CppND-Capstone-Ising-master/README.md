# CppND: Capstone Interactive 2D Ising model

This my Capstone project for the Udacity C++ Nanodegree.

##### Table of Contents 
- [Introduction](#introduction)
    - [Example Simulation Flow](#example-simulation-flow)
    - [Keyboard Interaction](#keyboard-interaction)
- [Dependencies](#dependencies)
    - [Basic Build Instructions](#basic-build-instructions)
- [Project Files](#project-files)
- [Rubric Points](#rubric-points)

## Introduction
Capstone project for [Udacity's C++ Nanodegree program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) 
 consisting on an implementation of the [2D Ising model](https://en.wikipedia.org/wiki/Ising_model) using the
  Metropolis Monte Carlo algorithm.

Most codes available requires the user to set the parameters of the simulation by changing the code and recompiling. 
 Here, The 2D Ising model is implemented in C++ combined with the [SDL library](https://www.libsdl.org/) that allows 
  the user to change simulation parameters interactively without having to change the code.
 
The user can change the following parameters (see the [table](#keyboard-interaction) below for all possible keyboard 
 interaction):
- Lattice size
- Temperature of the system
- Initial probability of spin distribution
- Number of frames to skip for rendering

#### Example Simulation Flow
The program starts in "paused" mode with a default lattice size of 100x100, temperature value of 1.0 and the spins
 are initialized randomly with a probability of 0.5. Pressing the `space` key starts the simulation (Note: the
  simulation can be paused interactively using the `space` key at anytime). Once the spins have converged (i.e., 
   either all pointing up or down), the simulation will be paused. The `R` key resets the simulation with the
    current lattice size and temperature value. Once a simulation is completed you can save the results by pressing
     the `S` key. The temperature, energy and spin state at each step is printed to a text file called
      "ising2d_results.txt". The results can be visualized using `gnuplot` or `python-matploblit` etc.
  
It is possible for the simulation to fall into a local minimum (i.e., the lattice never reaches a state where all the 
 spins are pointing up or down). Instead of waiting a really long time for the simulation to converge or restarting
  the simulation, it is possible to get out of the local minimum by increasing the temperature. By pressing the `H` 
   key, the temperature of the simulation is increased by 0.1 up to a maximum value of 3.0 interactively while the
    simulation is running. This will "uncluster" the spins, i.e. randomizing the spins. Then the lattice can be cooled 
     slowly (annealing) or quickly (quenching) by pressing the `C` key (also in steps of 0.1).

#### Keyboard Interaction
The user can interact with the simulation using the following keys:

| Key             | Action                                  | 
| :-------------: |:----------------------------------------|
| Up              | Increase lattice size                   |
| Down            | Decrease lattice size                   |
| Right           | Increase number of frames to skip       |
| Left            | Decrease number of frames to skip       | 
| H               | Increase temperature of system          |
| C               | Decrease temperature of system          |
| P               | Increase initial probability            |
| O               | Decrease initial probability            |
| S               | Save simulation results                 |
| SPACE           | Pause the simulation                    |
| R               | Restart the simulation                  |
| ESC             | Exit the simulation                     |

The program will print to the terminal a "feedback" when any of the key above is pressed.

Below are the possible ranges/values for the configurable parameters
- Lattice size (Default: 100 | N: 10, 20, 50, 100, 200, 500, 1000)
- Temperature (Default: 1.0 | T:0.1 &rarr; 3.0 in steps of 0.1)
- Probability (Default: 0.5 | P: 0.1 &rarr; 0.9 in steps of 0.1)
- Frame skip (Default: 1 | sf: 1 &rarr; 100 in steps of 10)

## Dependencies 
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
  
### Basic Build Instructions  
  1. Clone this repo.
  2. Make a build directory in the top level directory: `mkdir build && cd build`
  3. Compile: `cmake .. && make`
  4. Run it: `./Ising2D`
  
## Project Files

### `main.cpp`
[main.cpp](src/main.cpp) is the entry point for the program. The `main` function in this file sets the default
 values for the screen width and height (480x480) and initial lattice size (100x100). Then, the `main` function
  creates instances of the `Renderer`, `Controller` and `Simulator` class. Finally, the simulation is started by
   calling the `Simulation::Run` method.

### `renderer.h` and `renderer.cpp`
[renderer.h](src/renderer.h) and [renderer.cpp](src/renderer.cpp) defines the `Renderer` class, which uses the SDL
 library to render the spins on the screen. The `Renderer` class constructor creates the SDL window an SDL renderer
  object that can draw in to the window. The `Renderer::Render` method draws the current lattice state to the window
   using the SDL renderer. The `Renderer` class also includes the `Renderer::UpdateWindowTitle` that updates the
    window title with the following information:
- Current step
- Lattice size
- Current temperature
- Initial spin probability
- Frame skip
- Simulation state (paused or running)

### `controller.h` and `controller.cpp`
[controller.h](src/controller.h) and [controller.cpp](src/controller.cpp) defines the `Controller` class. This class
 handles keyboard input from the user using the [SDL2](https://www.libsdl.org/) library. See 
  [table](#keyboard-interaction) above for the possible keyboard interaction.

### `simulator.h` and `simulator.cpp`
[simulator.h](src/simulator.h) and [simulator.cpp](src/simulator.cpp) defines the `Simulator` class, which controls
 the flow of the simulation. This class creates the `Ising2D` instance and contains the `Simulator::Run` method. This
  method is adapted from the [Snake game](https://github.com/udacity/CppND-Capstone-Snake-Game) example where the
   method includes a "game" while loop. In this loop, the method continuously checks for any user key input and runs
    the Ising simulation including rendering the spins with the `Renderer::Render` method.
 
### `ising.h` and `ising.cpp`
[ising.h](src/ising.h) and [ising.cpp](src/ising.cpp) defines the `Ising2D` class. This class creates the lattice
 (container) for the spins, initializes the spins and flips the spins randomly using the Metropolis Monte Carlo
  algorithm. There are also a number of getter methods and controller specific methods.

### `array.h`
[array.h](src/array.h) define a template class I created that acts as an API for 1D and 2D array. This API makes it
 easier to deal with multi-dimensional arrays using a 1D `std::vector` container. The 2D class inherits the 1D class
  and can be extended to 3D arrays as well (but not implemented here). There a number of methods built in to the API
   like `reset`, which deletes all elements of the array and shrinks the array. Also, operator overloading is
    implemented in the class, e.g. an array equal to a number sets all the element of the array to that number. The
     `Array2D` class is used to define the lattice in `Ising2D`.

## Rubric Points
Below are the rubric points that are addressed/implemented in this project.

### Loop, Functions, I/O
- The project demonstrates an understanding of C++ functions and control structures.
- The project reads data from a file and process the data, or the program writes data to a file. (see line 79 in
 `simulator.cpp`, the `Simulator::write_results` method writes the results of the simulation to a text file)
- The project accepts user input and processes the input (this is done in the form of a keyboard interaction from the
 user, see `controller.cpp` from line 14).

### Object Oriented Programming
- The project uses Object Oriented Programming techniques.
- Classes use appropriate access specifiers for class members (see `simulator.h`, `controller.h`, `renderer.h` and
 `ising.h`).
- Class constructors utilize member initialization lists (see line 5 in `ising.cpp` for an example).
- Classes abstract implementation details from their interfaces.
- Classes encapsulate behavior.
- Templates generalize functions in the project (see implementation of an array API in `array.h`).
- Overloaded functions allow the same function to operate on different parameters (see line 57, 65 and 112 in `array.h`).
- Classes follow an appropriate inheritance hierarchy (see  class in `array.h`).

### Memory management
- The project makes use of references in function declarations.
- The project uses destructors appropriately (see line 36 in `renderer.cpp`).
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate (see constructor in
 `renderer.cpp`).
