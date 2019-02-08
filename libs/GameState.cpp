#include <iostream>
#include <cmath>
#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{
	GameState::GameState(GameDataRef _data) : data(_data){

	}

	void GameState::init(){
		for (int i = 1; i <= 9; i++)
		{
			t[i].loadFromFile("res/" + std::to_string(i) + ".png");
			t[i].setSmooth(true);
			object[i].setTexture(t[i]);
		}
		for(int i = 0; i < TOTAL_CARS; i++)
		{
			data->assets.load_texture("CarImage"+std::to_string(i),CAR_IMAGE_FILEPATH(i));
		}
		data->assets.load_texture("GameStateBackground", GAME_STATE_BACKGROUND_FILEPATH);
		data->assets.get_texture("GameStateBackground").setRepeated(true);
		background_sprite.setTexture(data->assets.get_texture("GameStateBackground"));
		background_sprite.setTextureRect(sf::IntRect(0, 0, 6000, 411));
		background_sprite.setPosition(-2000, 0);

		for (int i = 0; i < 1600; i++)
		{
			Line line;
			line.z = i * segL;
			if (i > 300 && i < 700)
				line.curve = 0.5;
			if (i > 1100)
				line.curve = -0.7;

			if (i < 300 && i % 20 == 0)
			{
				line.spriteX = -2.5;
				line.sprite = object[5];
			}
			if (i % 17 == 0)
			{
				line.spriteX = 2.0;
				line.sprite = object[6];
			}
			if (i > 300 && i % 20 == 0)
			{
				line.spriteX = -0.7;
				line.sprite = object[4];
			}
			if (i > 800 && i % 20 == 0)
			{
				line.spriteX = -1.2;
				line.sprite = object[1];
			}
			if (i == 400)
			{
				line.spriteX = -1.2;
				line.sprite = object[7];
			}

			if (i > 750)
				line.y = sin(i / 30.0) * 1500;

			// if (i > 300 && i < 800)	line.curve = 1;
			// if (i > 1100)line.curve = -0.7;
			// if (i < 300 && i % 20 == 0)
			// {
			// 	line.spriteX = -2.5;
			// 	line.sprite = object[5];
			// }
			// if (i % 17 == 0)
			// {
			// 	line.spriteX = 2;
			// 	line.sprite = object[6];
			// }
			// if (i > 300 && i % 20 == 0)
			// {
			// 	line.spriteX = -2;
			// 	line.sprite = object[4];
			// }
			// if (i > 800 && i % 20 == 0)
			// {
			// 	line.spriteX = -2;
			// 	line.sprite = object[1];
			// }
			// if (i == 400)
			// {
			// 	line.spriteX = -2;
			// 	line.sprite = object[7];
			// }
			// if (i > 750)line.y = sin(i / 30.0) * 1500;
			lines.push_back(line);
		}
		N = lines.size();
		car = std::unique_ptr<Cars>(new Cars(data,5,speed,playerX));
		bot = std::unique_ptr<Bot>(new Bot(data, 5));
		current_time=clock.getElapsedTime().asSeconds();
	}

	void GameState::handle_input(){
		sf::Event event;
		while(data->window.pollEvent(event))
			if(sf::Event::Closed==event.type){
				data->window.close();
			}

		new_time=clock.getElapsedTime().asSeconds();
		car->update_car(new_time - current_time,lines,pos,segL);
		// std::cout << new_time - current_time<<std::endl;
		current_time = new_time;
		pos += speed;
		while (pos >= N * segL)
			pos -= N * segL;
		while (pos < 0)
			pos += N * segL;
	}

	void GameState::draw_quad(sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2)
	{
		sf::ConvexShape shape(4);
		shape.setFillColor(c);
		shape.setPoint(0, sf::Vector2f(x1 - w1, y1));
		shape.setPoint(1, sf::Vector2f(x2 - w2, y2));
		shape.setPoint(2, sf::Vector2f(x2 + w2, y2));
		shape.setPoint(3, sf::Vector2f(x1 + w1, y1));
		data->window.draw(shape);
	}

	void GameState::project(Line &line, int camX, int camY, int camZ)
	{
		line.scale = camD / (line.z - camZ);
		line.X = (1 + line.scale * (line.x - camX)) * width / 2;
		line.Y = (1 - line.scale * (line.y - camY)) * height / 2;
		line.W = line.scale * roadW * width /2;
	}

	void GameState::drawSprite(Line &line)
	{
		s = line.sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * line.spriteX * width / 2;
		float destY = line.Y + 4;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;

		destX += destW * line.spriteX; //offsetX
		destY += destH * (-1);		   //offsetY

		float clipH = destY + destH - line.clip;
		if (clipH < 0)clipH = 0;
		if (clipH >= destH)	return;
		s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		data->window.draw(s);
	}

	void GameState::draw(float delta){
		data->window.clear(sf::Color(105, 205, 4));
		data->window.draw(background_sprite);
		int startPos = pos / segL;
		int camH = lines[startPos].y + H;
		// if (speed > 0)background_sprite.move(-1*lines[startPos].curve * 2, 0);
		// if (speed < 0)background_sprite.move(lines[startPos].curve * 2, 0);
		int maxy=height;
		float x=0,dx=0;
		for (int n = startPos; n < startPos + 500; n++)
		{
			Line &l = lines[n % N];

			project(l,playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0));
			x += dx;
			dx += l.curve;

			l.clip = maxy;
			if (l.Y >= maxy)continue;
			maxy = l.Y;

			sf::Color grass = (n / 3) % 2 ? sf::Color(16, 200, 16) : sf::Color(0, 154, 0);
			sf::Color marking = (n / 3) % 2 ? sf::Color::White : sf::Color(105, 105, 105);
			sf::Color rumble = (n / 3) % 2 ? sf::Color(255, 255, 255) : sf::Color(0, 0, 0);
			sf::Color road = (n / 3) % 2 ? sf::Color(107, 107, 107) : sf::Color(105, 105, 105);

			Line p = lines[(n - 1) % N];

			// drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
			// drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
			// drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
			draw_quad(grass, 0, p.Y, width, 0, l.Y, width);
			draw_quad(rumble, p.X, p.Y, p.W *1.1, l.X, l.Y, l.W * 1.1);
			draw_quad(road, p.X, p.Y, p.W, l.X, l.Y, l.W);
			draw_quad(marking,(p.X),p.Y,p.W*0.35,l.X,l.Y,l.W*0.35);
			draw_quad(road, p.X, p.Y, p.W*0.3, l.X, l.Y, l.W*0.3);

		}
		for (int n = startPos + 500; n > startPos; n--)
		{
			drawSprite(lines[n % N]);
		}
		bot->drawSprite(lines[bot_pos]);
		bot_pos++;
		bot_pos%=N;
		// if(bot_pos>1000)bot_pos=0;

		car->draw_car();
		data->window.display();
	}

	void GameState::update(float delta){

	}
}