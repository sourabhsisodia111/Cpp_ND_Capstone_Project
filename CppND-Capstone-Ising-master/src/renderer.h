#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "ising.h"
#include "controller.h"

class Renderer {
public:
    Renderer(const std::size_t &screen_width,
             const std::size_t &screen_height);
    ~Renderer();

    void Render(Ising2D &ising);
    void UpdateWindowTitle(int &step, Ising2D &ising, InputState &state);

    int skip_frame;

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
};

#endif //RENDERER_H