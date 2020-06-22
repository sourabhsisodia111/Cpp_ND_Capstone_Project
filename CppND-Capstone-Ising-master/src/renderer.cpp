#include "renderer.h"

Renderer::Renderer(const std::size_t &screen_width, const std::size_t &screen_height)
        : screen_width(screen_width),
          screen_height(screen_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("2D Ising Model",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  screen_width,
                                  screen_height,
                                  SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Frame skip
    skip_frame = 1;
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Ising2D &ising) {
    // Spin pixel size
    SDL_Rect block;
    block.w = std::ceil(static_cast<float>(screen_width) / static_cast<float>(ising.get_ncol()));
    block.h = std::ceil(static_cast<float>(screen_height) / static_cast<float>(ising.get_nrow()));

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render spins
    SDL_Renderer *renderer = sdl_renderer;
    for (int i = 0; i < ising.get_nrow(); i++) {
        block.x = i * block.w;
        for (int j = 0; j < ising.get_ncol(); j++) {
            block.y = j * block.h;
            if (ising.get_element(i, j) == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else if (ising.get_element(i, j) == -1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &block);
        }
    }

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int &step, Ising2D &ising, InputState &state) {
    if (state.pause) { // Window title when "paused"
        std::string title{
                "step: " + std::to_string(step)
                + " | " + std::to_string(ising.get_nrow()) + "x" + std::to_string(ising.get_ncol())
                + " | P: " + std::to_string(ising.get_prob())
                + " | T: " + std::to_string(ising.get_temp())
                + " | skip: " + std::to_string(skip_frame)
                + " | paused"
        };
        SDL_SetWindowTitle(sdl_window, title.c_str());
    } else { // Window title when "running"
        std::string title{
                "step: " + std::to_string(step)
                + " | " + std::to_string(ising.get_nrow()) + "x" + std::to_string(ising.get_ncol())
                + " | P: " + std::to_string(ising.get_prob())
                + " | T: " + std::to_string(ising.get_temp())
                             + " | skip: " + std::to_string(skip_frame)
                + " | running"
        };
        SDL_SetWindowTitle(sdl_window, title.c_str());
    }
}