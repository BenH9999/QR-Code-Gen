#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Screen{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int HEIGHT;
        int WIDTH;
        int grid_size;      
    public:
        Screen(int h, int w, int grid_size);
        Screen();
        ~Screen();
        bool init();
};