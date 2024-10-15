#include "gen.hpp"

gen::gen(Type grid_type){
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
