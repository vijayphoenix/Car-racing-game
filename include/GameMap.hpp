#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Line.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "PlayerCar.hpp"
#include "Camera.hpp"

namespace cp{
	class GameMap{
		private:
		////////// Data related to game ( assets, states, renderer, ... ) ////////
        GameDataRef data;
        /////////////////////////////////////////
		public:
		/////////// The GameMap ////////////////////
        std::vector<Line>lines;
        sf::Texture t[10];
        sf::Sprite  object[10];

        int         N;				// Total Grid count
        ///////////////////////////////////////////
		sf::Sprite  background_sprite;
        int         width   = SCREEN_WIDTH;
        int         height  = SCREEN_HEIGHT;
        int         roadW   = 4000; // Width of the road(RealW)
        int         segL    = 200;	//segment length

		void init		        ();
        void draw_quad          (sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
		void update             (float delta);
		void project(Line &line, int camX, int camY, int camZ, float camD);
		void draw(int count, std::unique_ptr<PlayerCar> &car, Camera& main_camera);
        void drawSprite (Line &line);

		GameMap (GameDataRef _data);
	};
}
#endif //GAME_MAP_HPP