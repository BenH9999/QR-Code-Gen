#include "gen.hpp"
#include <vector>
#include <cmath>

gen::gen(Type grid_type, std::string input){
    this->grid_size = 21 + (grid_type - 1) *4;
    this->grid_type = grid_type;

    this->target = input;
    this->qr_grid = std::vector<std::vector<int>>(grid_size, std::vector<int>(grid_size, 0));
}

void gen::gen_qr(){
    //Generate the finder pattern
    for(const Vector2& coords : generate_finder_pattern(0, 0))
        this->qr_grid[coords.x][coords.y] = 1;
    for(const Vector2& coords : generate_finder_pattern(0, grid_size - 7))
        this->qr_grid[coords.x][coords.y] = 1;
    for(const Vector2& coords : generate_finder_pattern(grid_size - 7, 0))
        this->qr_grid[coords.x][coords.y] = 1;

    //Generate allignment pattern
    if(this->grid_type != EMPTY && this->grid_type != VER1){
        for(const Vector2& coords : generate_allignment_pattern())
            this->qr_grid[coords.x][coords.y] = 1;
    }

    Screen s(grid_size, qr_grid);
}

std::vector<Vector2> gen::generate_allignment_pattern(){
    std::vector<Vector2> allignment_coords;
    std::vector<Vector2> center_points;
    std::<vector<int> row_cols;
    
    row_cols.push_back(6);

    if(this->grid_type < 7){
        int position = this->grid_size - 7;
        row_cols.push_back(position);
    }
    else{
        int num_rows_cols = std::ceil((double)(this->grid_type+2)/7.0)+1;

        int diff_rows_cols = (grid_size -13) / (num_rows_cols -1);

        for(int i = 1; i < num_rows_cols; i++){
            int position = 6 + i * diff_rows_cols;
            row_cols.push_back(position);
        }
    }

    return allignment_coords;
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
