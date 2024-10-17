#pragma once

#include "Screen.hpp"

class gen{
    private:
        Type grid_type;
        int grid_size;

        std::vector<std::vector<int>> qr_grid;
        std::string target;
    public:
        gen(Type grid_type, std::string input);
        gen();
        Type get_type();
        int get_size(); 

        void gen_qr();
        void generate_finder_pattern(int x, int y);
        void generate_allignment_pattern();
        void generate_timer_pattern();
        void reserve_format_version();
};
