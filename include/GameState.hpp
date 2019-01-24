#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Cars.hpp"
#include "State.hpp"
#include "Game.hpp"

namespace cp
{
	class GameState : public State
	{
		private:
		GameDataRef data;
		sf::Clock clock;
		sf::Sprite background_sprite;
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		int roadW = 2000;
		int segL = 200;	//segment length
		float camD = 0.84; //camera depth

		struct Line
		{
			float x=0, y=0, z=0; //3d center of line
			float X, Y, W; //screen coord
			float curve=0, spriteX=0, clip;
			float scale;
			sf::Sprite sprite;
		};

		sf::Texture t[10];
		// sf::Texture car_image[10];
		sf::Sprite object[10];
		std::vector<Line>lines;

		int N;
		float speed = 0;
		int acceleration=1,decleration=-5;
		float playerX = 0;
		int pos = 0;
		int H = 1500;
		float new_time,current_time, time_difference;
		void project(Line &line, int camX, int camY, int camZ);

		void drawSprite(Line &line);

		Cars *car;

		void increase(bool nitro);

		void decrease(bool brakes);

	  public:
		GameState(GameDataRef _data);
		// ~GameState();

		void init();
		void handle_input();
		void draw(float delta);
		void draw_quad(sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
		void update(float delta);
	};
} // namespace cp

#endif //GAMESTATE_HPP