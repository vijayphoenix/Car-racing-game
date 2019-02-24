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
        void init		            ();
        void handle_input       ();
        void draw               (float delta);
        void update             (float delta);
        void drawSprite         (Line &line);
        static void network_handler(GameDataRef data, std::shared_ptr<PlayerCar> car);

        typedef std::shared_ptr<PlayerCar> CarRef;

        private:
          ////////// Data related to game ( assets, states, renderer, ... ) ////////
          GameDataRef data;
        /////////////////////////////////////////

        ////////// The Game clock ///////////////
        sf::Clock  clock;
        float       current_time=0;
        float       new_time=0;
        ///////////////////////////////////////

        /////////// The GameMap ////////////////////
        GameMap map;
        //////////////////////////////////////////
        sf::Sprite  s;

        Camera main_camera;


        ///////// The Bots drones.. /////////
        std::unique_ptr<Bot>    bot[TOTAL_BOTS];
        //////////////////////////////////

        ///////// The player Car ////////
        CarRef   car;
        //////////////////////////////////

        ///////// The collision Handler ///
        Collision               collision;
        ///////////////////////////////////


        std::thread network_handle;
    };
} // namespace cp

#endif //GAMESTATE_HPP