#include "gen.hpp"

gen::gen(Type grid_type, std::string input){
    switch(grid_type){
        case EMPTY:{
            this->grid_size = 5;
        }
        case VER1:{
            this->grid_size = 21;
        }
        case VER2:{
            this->grid_size = 25;
        }
    }

    this->target = input;
    this->qr_grid = std::vector<std::vector<int>>(grid_size, std::vector<int>(grid_size, 0));
}

void gen::gen_qr(){
    //Generate the finder pattern
    for(const Vector2& coords : generate_finder_pattern(0, 0)) this->qr_grid[coords.x][coords.y] = 1;
    for(const Vector2& coords : generate_finder_pattern(0, grid_size - 7)) this->qr_grid[coords.x][coords.y] = 1;
    for(const Vector2& coords : generate_finder_pattern(grid_size - 7, 0)) this->qr_grid[coords.x][coords.y] = 1;

    Screen s(grid_size, qr_grid);
}

std::vector<Vector2> gen::generate_finder_pattern(int x, int y){
    std::vector<Vector2> pattern_coords;

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){

            if(i == 0 || i == 6 || j == 0 || j == 6) pattern_coords.push_back({x + i, y +j});
            else if(i >= 2 && i <= 4 && j >= 2 && j <=4) pattern_coords.push_back({x + i, y + j});
        }
    }
        
    
    return pattern_coords;
}

gen::gen(){
    this->grid_type = EMPTY;
    this->grid_size = 5;
}

Type gen::get_type(){
    return this->grid_type;
}

int gen::get_size(){
    return this->grid_size;
}
