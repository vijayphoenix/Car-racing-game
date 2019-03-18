#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Objects/Line.hpp"
#include "States/State.hpp"
#include "Game.hpp"
#include "Objects/PlayerCar.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Car.hpp"
#include "Objects/Bot.hpp"
#include "Objects/Bullet.hpp"

namespace cp{
	class GameMap{
		private:
		////////// Data related to game ( assets, states, renderer, ... ) ////////
        GameDataRef data;
        /////////////////////////////////////////
        /////////// GameMap Components //////////
        sf::Texture t[10];
        sf::Sprite  object[10];
		sf::Sprite  background_sprite;
        ///////////////////////////////////////////
        int         width   = SCREEN_WIDTH;
        int         height  = SCREEN_HEIGHT;
        int         N;				// Total Grid count

        int         roadW   = 4000; // Width of the road(RealW)
        int         segL    = 200;	//segment length

		public:
		/////////// The GameMap ////////////////////
        std::vector<Line> lines;
        // std::vector<Line> lines;

		GameMap                 (GameDataRef _data);
		void init		        ();
        void draw_quad          (sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
		void update             (float delta);
        void project            (Line &line, float camX, float camY, float camZ, float camD);
        void draw               (int count, const Camera& main_camera);
        void drawSprite         (const Line &line);
        int  get_grid_index     (float distance);
        void bound_entity       (cp::Car &car);
        void bound_entity       (Camera& camera);
        void bound_entity(Bullet &bot);
        void bound_entity(Bot &bot);
        int getRoadWidth() const;
        int getSegL() const;
        int getGridCount() const;
        int getScreenWidth() const;
        int getScreenHeight() const;
    };
}
#endif //GAME_MAP_HPP