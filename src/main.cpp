
#include "test.hpp"
#include <SDL2/SDL.h>
#undef main
#include <iostream>

void test::bad(){
    std::cout << "Hello!" << std::endl;
}

int main(){
    test::bad();

    return 0;
}