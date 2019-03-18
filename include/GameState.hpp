#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include "GameOverState.hpp"
#include "BustedState.hpp"
#include "DEFINITIONS.hpp"
#include "Bot.hpp"
#include "PlayerCar.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Line.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "GameMap.hpp"
#include "PauseState.hpp"
#include "PercentageBar.hpp"
#include "Bullet.hpp"
#include "ObjectPool.hpp"

namespace cp
{
    class GameState : public State {
        public:

        GameState               (GameDataRef _data);
        ~GameState              () {}
        void init		            ();
        void handle_input       (float delta);
        void draw               (float delta);
        void update             (float delta);
        void drawSprite         (Line &line);
        static void network_handler(GameDataRef data, std::shared_ptr<PlayerCar> car, std::shared_ptr<Bot> bot);

        typedef std::shared_ptr<PlayerCar> CarRef;

        private:
        ////////// Data related to game ( assets, states, renderer, ... ) ////////
        GameDataRef data;
        /////////////////////////////////////////

        ////////// The Game clock ///////////////
        // sf::Clock  clock;
        // float       current_time=0;
        // float       new_time=0;
        ///////////////////////////////////////

        /////////// The GameMap ////////////////////
        GameMap map;
        //////////////////////////////////////////
        sf::Sprite  s;

        Camera main_camera;


        ///////// The Bots drones.. /////////
        std::shared_ptr<Bot>    bot[TOTAL_BOTS];
        //////////////////////////////////

        ///////// The player Car ////////
        CarRef   car;
        //////////////////////////////////

        ///////// The collision Handler ///
        Collision               collision;
        ///////////////////////////////////


        std::thread network_handle;

        PercentageBar bar;
        sf::Font font;
        sf::Text text[5];
        long long int score=0;
        // float fuel =100;
        ObjectPool<Bullet>pool;
        Bullet* bullet;
        std::set<Bullet*> bullet_set[2];
        int current=0;
}; // namespace cp
}

#endif //GAMESTATE_HPP