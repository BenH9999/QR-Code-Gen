#pragma once

#include <SDL2/SDL.h>
#include "gen.hpp"
#include <iostream>

class Screen{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int window_size;
        const int SCALE = 25;
    public:
        Screen(int grid_size);
        Screen();
        ~Screen();
        bool init();
};
