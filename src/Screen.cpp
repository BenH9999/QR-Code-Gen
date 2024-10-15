#include "Screen.hpp"

Screen::Screen(int grid_size){
    this->window = nullptr;
    this->renderer = nullptr;
    this->window_size = grid_size * SCALE;
}

Screen::Screen(){
    this->window = nullptr;
    this->renderer = nullptr;
    this->window_size = 5 * SCALE;
}

bool Screen::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "Error initialising SDL:" << SDL_GetError() << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    this->window = SDL_CreateWindow("QR Code", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size, window_size, 0);
    if(!this->window){
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if(!this->renderer){
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        system("pause");
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(renderer, 255,0,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    while(true){
        while(SDL_PollEvent(&e)!=0){
		    if(e.type == SDL_QUIT) exit(0);
    	}
    }

    return EXIT_SUCCESS;
}

Screen::~Screen(){

}
