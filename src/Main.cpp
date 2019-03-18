#include "DEFINITIONS.hpp"
#include <time.h>
#include "Game.hpp"

#include <iostream>

int main()
{
    srand(time(NULL));
    cp::Game(SCREEN_WIDTH,SCREEN_HEIGHT, "SFML POPL2 Chor Police Project");
    std::cout<<"---hi---"<<std::endl;
    return EXIT_SUCCESS;
}
