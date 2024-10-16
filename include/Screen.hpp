#pragma once

#include <SDL2/SDL.h>
#include "util.hpp"

#include <iostream>

class Screen{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int window_size;
        int SCALE;
    public:
        Screen(int grid_size, std::vector<std::vector<int>> grid);
        Screen();
        ~Screen();
        bool init();

        void draw_qr(std::vector<std::vector<int>> grid, int grid_size);
};
