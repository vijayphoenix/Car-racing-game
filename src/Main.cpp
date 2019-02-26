#include "DEFINITIONS.hpp"
#include "Game.hpp"

#include <iostream>

int main()
{
    cp::Game(SCREEN_WIDTH,SCREEN_HEIGHT, "SFML POPL2 Chor Police Project");
    std::cout<<"---hi---"<<std::endl;
    return EXIT_SUCCESS;
}
