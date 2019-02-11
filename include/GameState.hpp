#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Bot.hpp"
#include "Cars.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Line.hpp"
#include "Collision.hpp"
#include <memory>


namespace cp
{
    class GameState : public State {
        public:
        /////////// The GameMap ////////////////////
        std::vector<Line>lines;
        ///////////////////////////////////////////

        GameState               (GameDataRef _data);
        ~GameState              () {}
        void init		        ();
        void handle_input       ();
        void draw               (float delta);
        void draw_quad          (sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
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

        sf::Sprite  background_sprite;
        int         width   = SCREEN_WIDTH;
        int         height  = SCREEN_HEIGHT;
        int         roadW   = 4000; // Width of the road(RealW)
        int         segL    = 200;	//segment length
        float       camD    = 0.84; //camera depth

        sf::Texture t[10];
        sf::Sprite  object[10];
        sf::Sprite  s;

        int         N;				// Total Grid count
        int         temp=0;
        float       speed = 0;		// The Camera speed
        float       playerX = 0;	// The players X position in 3D
        int         pos = 0;	    // The players Z position
        int         H = 1500;       // The Camera height

        ///////// The Bots drones.. /////////
        std::unique_ptr<Bot>    bot[TOTAL_BOTS];
        int                     bot_pos[TOTAL_BOTS] ={};
        //////////////////////////////////

        ///////// The player Car ////////
        std::unique_ptr<Cars>   car;
        //////////////////////////////////

        ///////// The collision Handler ///
        Collision               collision;
        ///////////////////////////////////

        void project    (Line &line, int camX, int camY, int camZ);
        void drawSprite (Line &line);


        ///////// Debug Temp Functions ////
        void handle_road_width(int dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                roadW+=dt;
                std::cout<<"Increased road width "<<roadW<<std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                roadW-=dt;
                std::cout<<"Decreased road width "<<roadW<<std::endl;
            }
        }
        void handle_segL(int dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                segL+=dt;
                std::cout<<"Increased segL width "<<segL<<std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                segL-=dt;
                std::cout<<"Decreased segL width "<<segL<<std::endl;
            }
        }
        void handle_camD(float dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                camD+=dt;
                std::cout<<"Increased camD width "<<camD<<std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                camD-=dt;
                std::cout<<"Decreased camD width "<<camD<<std::endl;
            }
        }
        //////////////////////////////////////
    };
} // namespace cp

#endif //GAMESTATE_HPP