#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1024//sf::VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT 768//sf::VideoMode::getDesktopMode().height

#define SPLASH_STATE_SHOW_TIME 1.0
#define SPLASH_SCENE_BACKGROUND_FILEPATH "res/splashScreen.png"

#define MAIN_MENU_BACKGROUND_FILEPATH "res/splashScreen.png"

#define GAME_BACKGROUND_FILEPATH "res/sky.png"

// #define GAME_STATE_BACKGROUND_FILEPATH "res/bg.png"
// #define TREE1 "1.png"
// #define TREE2 "2.png"
// #define TREE3 "3.png"
// #define TREE4 "4.png"
// #define TREE5 "5.png"
// #define HOUSE "6.png"
// #define GRASS "7.png"
// #define HOUSE2 "8.png"
// #define TREE6 "9.png"
// #define CAR_IMAGE_FILEPATH(i) "res/car"+i+".png"
// #define GAME_STATE_BACKGROUND_FILEPATH "res/cy.png"
// #define CAR_IMAGE_FILEPATH "res/Car_main.png"
#define GAME_STATE_BACKGROUND_FILEPATH "res/cy.png"
#define TOTAL_CARS 9
#define CAR_IMAGE_FILEPATH(i) CAR_NAME(i)
static std::string CAR_NAME(int x){return ("res/CarImage"+ std::to_string(x)+".png");}
#define GAME_OVER_BACKGROUND_FILEPATH "res/sky.png"
#define GAME_TITLE_FILEPATH "res/title.png"
#define PLAY_BUTTON_FILEPATH "res/PlayButton.png"
#define PIPE_UP_FILEPATH "res/PipeUp.png"
#define PIPE_DOWN_FILEPATH "res/PipeDown.png"
#define ROAD_WIDTH 2000
#define SEGMENT_LENGTH 200
#define CAMERA_DEPTH 0.84f
const sf::Vector2f Scaling_factor(1368.0f / 1920.0f, 768.0f / 1080.0f);

#endif //DEFINITIONS_HPP

