#ifndef CARS_HPP
#define CARS_HPP
#include <iostream>
#include "Car.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace cp{

	class Cars:public Car{

	public:
		Cars(GameDataRef _data,int _car_num,float &cspeed,float &cplayerX);
		~Cars();

		void update_car(float dt, std::vector<Line> &lines, float pos, float segL)
		{
			float speedRatio = cspeed / max_speed;
			float dx = 2 * dt * speedRatio;
			bool l=false,r=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				cplayerX -= dx;
				l=true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				cplayerX += dx;
				r=true;
			}

			cplayerX -= (dx * speedRatio * lines[pos/segL].curve * centrifugal);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				cspeed += acceleration * dt;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))cspeed += decleration * dt;
			else cspeed += friction * dt;
			// playerX=std::max(-2.0f,std::min(playerX,2.0f));
			cspeed = std::max(0.0f, std::min(cspeed, max_speed));
			car_image_num=5;

			if(cspeed > 0.1){
				if(l)car_image_num=3;
				else if(r)car_image_num=4;
				sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
				// sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - sprite.getGlobalBounds().height*(1.5+2*speedRatio*speedRatio));
				// sprite.setScale(3-speedRatio*speedRatio,3-speedRatio*speedRatio);
			}
		}

		void drawSprite(Line &line)
		{
			// s = line.sprite;
			sf::Sprite s = sprite;
			int SpriteX = -2.5;
			int w = s.getTextureRect().width;
			int h = s.getTextureRect().height;
			// h*=2;

			float destX = line.X + line.scale * SpriteX * SCREEN_WIDTH / 2;
			float destY = line.Y + 4;
			float destW = w * line.W / 266;
			float destH = h * line.W / 266;

			destX += destW * SpriteX; //offsetX
			destY -= destH;			  //offsetY

			float clipH = destY + destH - line.clip;
			if (clipH < 0)
				clipH = 0;
			if (clipH >= destH)
				return;
			// s.setTextureRect(sf::IntRect(0, 0, w,h - h * clipH / destH));
			s.setScale(destW / w, destH / h);
			s.setPosition(destX, destY);
			data->window.draw(s);
		}

		float centrifugal=0.5;
		float friction = -max_speed/5;

	private:
	float &cspeed;
	float &cplayerX;
	};
}
#endif //CARS_HPP