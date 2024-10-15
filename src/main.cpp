#include "Screen.hpp"
#undef main

std::string target = "https://github.com/BenH9999";

int main(){
    gen g(VER1);
    Screen s(g.get_size());
    s.init();

    return 0;
}
