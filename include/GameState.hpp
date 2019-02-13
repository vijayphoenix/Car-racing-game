#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Bot.hpp"
#include "PlayerCar.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Line.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "GameMap.hpp"
#include <memory>


namespace cp
{
    class GameState : public State {
        public:

        GameState               (GameDataRef _data);
        ~GameState              () {}
        void init		        ();
        void handle_input       ();
        void draw               (float delta);
        // void draw_quad          (sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
        void update             (float delta);

        private:
        ////////// Data related to game ( assets, states, renderer, ... ) ////////
        GameDataRef data;
        /////////////////////////////////////////

        ////////// The Game clock ///////////////
        sf::Clock   clock;
        float       current_time=0;
        float       new_time=0;
        ///////////////////////////////////////

        /////////// The GameMap ////////////////////
        GameMap map;
        //////////////////////////////////////////
        sf::Sprite  s;
        int         temp=0;

        Camera main_camera;


        ///////// The Bots drones.. /////////
        std::unique_ptr<Bot>    bot[TOTAL_BOTS];
        int                     bot_pos[TOTAL_BOTS] ={};
        //////////////////////////////////

        ///////// The player Car ////////
        std::unique_ptr<PlayerCar>   car;
        //////////////////////////////////

        ///////// The collision Handler ///
        Collision               collision;
        ///////////////////////////////////

        // void project    (Line &line, int camX, int camY, int camZ);
        void drawSprite (Line &line);


        ///////// Debug Temp Functions ////
        void handle_road_width(int dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                map.roadW+=dt;
                std::cout<<"Increased road width "<<map.roadW<<std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                map.roadW-=dt;
                std::cout<<"Decreased road width "<<map.roadW<<std::endl;
            }
        }
        void handle_segL(int dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                map.segL+=dt;
                std::cout<<"Increased map.segL width "<<map.segL<<std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                map.segL-=dt;
                std::cout<<"Decreased map.segL width "<<map.segL<<std::endl;
            }
        }
        void handle_camD(float dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                main_camera.camD+=dt;
                std::cout<<"Increased camD width "<<main_camera.camD<<std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                main_camera.camD-=dt;
                std::cout<<"Decreased camD width "<<main_camera.camD<<std::endl;
            }
        }
        //////////////////////////////////////
    };
} // namespace cp

#endif //GAMESTATE_HPP