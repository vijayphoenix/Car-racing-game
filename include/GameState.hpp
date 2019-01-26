#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Cars.hpp"
#include "State.hpp"
#include "Game.hpp"
#include <memory>
namespace cp
{
	class GameState : public State
	{
		private:
		GameDataRef data;
		sf::Clock clock;
		float current_time=0;
		float new_time=0;
		sf::Sprite background_sprite;
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		int roadW = 2000;
		int segL = 200;	//segment length
		float camD = 0.84; //camera depth

		struct Line
		{
			float x=0, y=0, z=0; //3d center of line
			float X=0, Y=0, W=0; //screen coord
			float curve=0, spriteX=0, clip=0;
			float scale=0;
			sf::Sprite sprite;
		};

		sf::Texture t[10];
		sf::Sprite object[10];
		sf::Sprite s;
		std::vector<Line>lines;

		int N;
		float speed = 0;
		// int acceleration=1,decleration=-5;
		float playerX = 0;
		int pos = 0;
		int H = 1500;
		// float new_time,current_time,time_difference;
		void project(Line &line, int camX, int camY, int camZ);

		void drawSprite(Line &line);

		std::unique_ptr<Cars> car;

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