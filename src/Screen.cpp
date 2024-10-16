#include "Screen.hpp"

Screen::Screen(int grid_size, std::vector<std::vector<int>> grid){
    this->window = nullptr;
    this->renderer = nullptr;
    this->SCALE = 25;

    while(grid_size * SCALE >725){
        this->SCALE--;
    }

    this->window_size = (grid_size + 8) * SCALE; //+8 for Quiet Zone
    this->init();
    this->draw_qr(grid, grid_size);
}

Screen::Screen(){
    this->window = nullptr;
    this->renderer = nullptr;
    this->window_size = 5 * SCALE;
}

void Screen::draw_qr(std::vector<std::vector<int>> grid, int grid_size){ 
    SDL_Rect rect;

    for(int y = 0; y < grid_size; y++){
        for (int x = 0; x < grid_size; x++){
            rect.x = (x+4)*SCALE; //+4 for Quiet Zone
            rect.y = (y+4)*SCALE;   
            rect.w = SCALE;
            rect.h = SCALE;

            switch(grid[x][y]){
                case 0:
                    SDL_SetRenderDrawColor(this->renderer,255,255,255,255);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(this->renderer,0,0,0,255);
                    break;
                default:
                    //Error
                    SDL_SetRenderDrawColor(this->renderer,255,0,0,255);
                    break;
            }
            SDL_RenderFillRect(this->renderer, &rect);
        }
    }
    
    SDL_SetRenderDrawColor(this->renderer, 200, 200, 200, 255);
    
    for (int x = 0; x <= grid_size; x++) {
        int x_pos = (x + 4) * SCALE;
        SDL_RenderDrawLine(this->renderer, x_pos, 4 * SCALE, x_pos, (grid_size + 4) * SCALE);
    }

    for (int y = 0; y <= grid_size; y++) {
        int y_pos = (y + 4) * SCALE;
        SDL_RenderDrawLine(this->renderer, 4 * SCALE, y_pos, (grid_size + 4) * SCALE, y_pos);
    }

    SDL_RenderPresent(this->renderer);

    SDL_Event e;
    bool running = true;

    while(running){
        while(SDL_PollEvent(&e)!=0){
            if(e.type == SDL_QUIT) running = false;
        }
    }

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
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

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer); 

    return EXIT_SUCCESS;
}

Screen::~Screen(){

}
