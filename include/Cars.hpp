#ifndef CARS_HPP
#define CARS_HPP
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace cp{

	class Cars{

	public:
		Cars(GameDataRef _data,int _car_num);
		~Cars();

		void draw_car();

		void update_car(float &speed, float dt, float &playerX, float curve)
		{
			std::cout<<dt<<std::endl;
			float speedRatio = speed / max_speed;
			float dx = 2 * dt * speedRatio;
			bool l=false,r=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				playerX -= dx;
				l=true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				playerX += dx;
				r=true;
			}

			playerX -= (dx * speedRatio * curve * centrifugal);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				speed += acceleration * dt;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))speed += decleration * dt;
			else speed += friction * dt;
			// playerX=std::max(-2.0f,std::min(playerX,2.0f));
			speed = std::max(0.0f, std::min(speed, max_speed));
			car_image_num=5;
			if(speed > 0.1){
				if(l)car_image_num=3;
				else if(r)car_image_num=4;
				sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
			}
		}
		float playerX=0;
		float speed=0;
		float position=0;
		float max_speed=400;
		float centrifugal=0.5;
		float acceleration=max_speed/5;
		float decleration = -max_speed;
		float friction = -max_speed/5;

	private:
		int car_image_num;
		GameDataRef data;
		sf::Sprite sprite;
		// float positionX;
	};
}
#endif //CARS_HPP