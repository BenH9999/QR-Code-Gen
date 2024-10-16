#include "gen.hpp"
#undef main

std::string target = "https://github.com/BenH9999";

int main(){
    int version;
    std::cout << "Enter QR Version:" << std::endl;
    std::cin >> version;

    gen g(Type(version), target);
    g.gen_qr();

    return 0;
}
