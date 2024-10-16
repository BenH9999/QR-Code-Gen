#include "gen.hpp"
#undef main

std::string target = "https://github.com/BenH9999";

int main(){
    gen g(VER1, target);
    g.gen_qr();

    return 0;
}
