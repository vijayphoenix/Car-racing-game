#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1024//sf::VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT 768//sf::VideoMode::getDesktopMode().height

// const int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
// const int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

#define SPLASH_STATE_SHOW_TIME 				1.0
#define SPLASH_SCENE_BACKGROUND_FILEPATH 	"../res/splashScreen.png"
#define MAIN_MENU_BACKGROUND_FILEPATH 		"../res/splashScreen.png"
#define GAME_BACKGROUND_FILEPATH 			"../res/sky.png"
#define GAME_STATE_BACKGROUND_FILEPATH 		"../res/cy.png"
#define GAME_OVER_BACKGROUND_FILEPATH 		"../res/busted.png"

#define PORT 20000
#define WAITING_ROOM_TIME 100000
#define MAX_EXTERNAL_PLAYER 4

#define TOTAL_CARS 10
#define TOTAL_BOTS 2
#define COEFFICIENT_OF_RESTITUTION 0.8
#define MAX_ENTITIES 1000


#define CAR_IMAGE_FILEPATH(i) CAR_NAME(i)
static std::string CAR_NAME(int x){return ("../res/CarImage"+ std::to_string(x)+".png");}
#define P_CAR_IMAGE_FILEPATH(i) P_CAR_NAME(i)
static std::string P_CAR_NAME(int x){return ("../res/PCarImage"+ std::to_string(x)+".png");}
#define FIRE_IMAGE_FILEPATH(i) FIRE_NAME(i)
static std::string FIRE_NAME(int x){return ("../res/f"+ std::to_string(x)+".png");}
#define Log(tag, message) std::cout<<tag<<" --> "<<message<<std::endl

#define GAME_TITLE_FILEPATH 	"../res/title.png"
#define RESUME_BUTTON_FILEPATH 	"../res/PlayButton3.png"
#define HOST_PLAY_BUTTON_FILEPATH 	"../res/PlayButton2_host.png"
#define JOIN_PLAY_BUTTON_FILEPATH 	"../res/PlayButton2_join.png"
#define SINGLE_PLAY_BUTTON_FILEPATH 	"../res/PlayButton1.png"
#define MENU_BUTTON_FILEPATH    "../res/MenuButton.png"

#define ROAD_WIDTH 		2000
#define SEGMENT_LENGTH 	200
#define CAMERA_DEPTH 	0.84f

const sf::Vector2f Scaling_factor(1368.0f / 1920.0f, 768.0f / 1080.0f);

#endif //DEFINITIONS_HPP

