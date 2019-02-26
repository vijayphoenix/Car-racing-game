#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include "GameOverState.hpp"
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
#include <memory>

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
        static void network_handler(GameDataRef data, std::shared_ptr<PlayerCar> car, std::shared_ptr<Bot> bot);



        private:
        void drawSprite         (Line &line);

        using CarRef = std::shared_ptr<PlayerCar>;
        using BotRef = std::shared_ptr<Bot>;
        GameDataRef data;
        GameMap map;
        Camera main_camera;
        CarRef player;
        CarRef    bot[TOTAL_BOTS];
        Collision               collision;
        // std::thread network_handle;
    };
} // namespace cp

#endif //GAMESTATE_HPP