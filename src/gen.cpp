#include "gen.hpp"
#include <vector>
#include <cmath>

gen::gen(Type grid_type, std::string input){
    this->grid_size = 21 + (grid_type - 1) *4;
    this->grid_type = grid_type;

    this->target = input;
    this->qr_grid = std::vector<std::vector<int>>(grid_size, std::vector<int>(grid_size, 2));
}

void gen::gen_qr(){
    //Generate the finder pattern
    generate_finder_pattern(0,0);
    generate_finder_pattern(0, grid_size - 7);
    generate_finder_pattern(grid_size - 7, 0);

    //Generate allignment pattern 
    if(this->grid_type != EMPTY && this->grid_type != VER1)
        generate_allignment_pattern();

    //Generate timing pattern
    generate_timer_pattern();

    //dark module
    this->qr_grid[8][(4*this->grid_type)+9] = 1;

    reserve_format_version();

    Screen s(this->grid_size, qr_grid);
}

void gen::generate_timer_pattern(){
    int i = 0;
    int j = 0;
    bool active = true;

    
    j = 6;
    for(i = 8; i < (this->grid_size - 8); i++){
        //horizontal
        this->qr_grid[i][j] = (active) ? 1 : 0;
        
        //vertical
        this->qr_grid[j][i] = (active) ? 1 : 0;
        active = (active) ? false : true;
    }
}

void gen::generate_allignment_pattern(){
    std::vector<Vector2> center_points;
    std::vector<int> row_cols;
    
    int intervals = this->grid_type / 7 + 1;
    int distance = 4 * this->grid_type + 4;
    int step = std::lround((double)distance/(double)intervals);
    step += step & 0b1;

    row_cols.push_back(6);

    for(int i = 1; i <= intervals; i++){
        int position = 6 + distance - step * (intervals - i);
        row_cols.push_back(position);
    }

    for(int i = 0; i < row_cols.size(); i++){
        for(int j = 0; j < row_cols.size(); j++){
            if ((i == 0 && j == 0) || (i == 0 && j == row_cols.size() - 1) || (i == row_cols.size() - 1 && j == 0)) continue;
            Vector2 temp = {row_cols[i],row_cols[j]};
            center_points.push_back(temp);
        }
    }

    for(const Vector2& center : center_points){
        for(int dy = -2; dy <= 2; dy++){
            for(int dx = -2; dx <= 2; dx++){
                Vector2 coord = {center.x +dx, center.y + dy};
                if(std::abs(dx) == 2 || std::abs(dy)== 2) this->qr_grid[coord.x][coord.y] = 1;
                else if(std::abs(dx) == 1 || std::abs(dy) ==1) this->qr_grid[coord.x][coord.y] = 0;
                else if(dx == 0 && dy == 0) this->qr_grid[coord.x][coord.y] = 1;
            }
        }
    }
}

void gen::reserve_format_version(){
    //format info
    for(int i = 0; i < 9; i++){
        if(i!=6){
            this->qr_grid[8][i] = 3;
            this->qr_grid[i][8] = 3;
        }
        if(i!=7 && i!=8)
            this->qr_grid[8][this->grid_size-i-1] = 3;
        if(i !=8)
            this->qr_grid[this->grid_size-i-1][8] = 3;

    }
    if(this->grid_type >= 7){
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 3; j++){
                this->qr_grid[i][this->grid_size-9-j] = 3;
                this->qr_grid[this->grid_size-9-j][i] = 3;
            }
        }
    }
}

void gen::generate_finder_pattern(int x, int y){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){                           
            if(i == 0 || i == 6 || j == 0 || j == 6) this->qr_grid[x+i][y+j] = 1;
            else if(i == 1 || i == 5 || j == 1 || j == 5) this->qr_grid[x+i][y+j] = 0;
            else if(i >= 2 && i <= 4 && j >= 2 && j <=4) this->qr_grid[x+i][y+j] = 1;    
        }
    } 

    for(int i = 0; i < 8 ; i++){
        if(x == y) {
            this->qr_grid[x+i][7] = 0;
            this->qr_grid[7][y+i] = 0;
        }
        else if(x != 0){
            this->qr_grid[x+i-1][this->grid_size - x] = 0;
            this->qr_grid[x-1][y+i] =0;
        }
        else if(y != 0){
            this->qr_grid[x+i][y-1] = 0;
            this->qr_grid[this->grid_size - y][y+i-1] = 0;
        }
    }
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
