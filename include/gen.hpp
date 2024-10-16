#pragma once

#include "Screen.hpp"

class gen{
    private:
        Type grid_type;
        int grid_size;

        std::vector<std::vector<int>> qr_grid;
        std::vector<Vector2> active_squares;
        std::string target;
    public:
        gen(Type grid_type, std::string input);
        gen();
        Type get_type();
        int get_size(); 

        void gen_qr();
        std::vector<Vector2> generate_finder_pattern(int x, int y);
};
