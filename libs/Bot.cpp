#include "Objects/Bot.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <cmath>
#include <sstream>


namespace cp
{
	Bot::Bot(GameDataRef _data, int car_num)
		:Car(_data, car_num) {
		/////// Setting up entity ////////
		e_speed = sf::Vector3f(0, 0, 0);
		e_max_speed = sf::Vector3f(0, 0, 300);
		///////////////////////////////////
		sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		health =50;
		e_position.x=-1.0;
		e_position.z = 4000;
		car_mass = 100;
		in_use = true;
	}
	Bot::~Bot() {
	}
	void Bot::drawSprite(const Line &line) {
		sf::Sprite &s=sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * e_position.x * SCREEN_WIDTH / 2;
		float destY = line.Y + 4;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;

		destX += destW * e_position.x;	  //offsetX
		destY -= destH;		   		 	  //offsetY

		float clipH = destY + destH - line.clip;
		if (clipH < 0)	clipH = 0;
		if (clipH >=destH)return;

		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		data->window.draw(s);
	}
	void Bot::update_car(const float dt, const std::vector<Line> &lines, const float segL) {
		e_position += e_speed;
		car_image_num = 5;
		if (health == 0){
			sprite.setTexture(data->assets.get_texture("f"+std::to_string((int)std::ceil(((float)(img++))/2))));
			if(img==25){
				*this = Bot(data , this->car_image_num);
				img=1;
			}
		}
		else if (std::abs(e_speed.z) > 0.1)
			{
				if (l)
					car_image_num = 3;
				else if (r)
					car_image_num = 4;
				sprite.setTexture(data->assets.get_texture("PCarImage" + std::to_string(car_image_num)));
			}
	}
	void Bot::handle_input(Bot::input_type mask, float dt) {
		float speedRatio = e_speed.z / e_max_speed.z;
		float dx = 2 * dt * speedRatio;
		l = r = false;
		if (mask[0])
		{
			e_speed.z += e_acceleration.z * dt;
		}
		else if (mask[1])
		{
			e_speed.z += e_decleration.z * dt;
		}
		e_speed.z = std::max(-50.0f, std::min(e_speed.z, e_max_speed.z));
		if (mask[2])
		{
			e_position.x -= dx;
			l = true;
		}
		else if (mask[3])
		{
			e_position.x += dx;
			r = true;
		}
		e_position += e_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			std::cout << "For Bot:" << e_position.x << " " << e_position.y << std::endl;
		}

	// void Bot::handle_input() {
	// 	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	// 	// {
	// 	// 	e_position.z -= 200;
	// 	// }
	// 	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	// 	// {
	// 	// 	// std::cout << "initial:" << e_position.z << std::endl;
	// 	// 	e_position.z += 400;
	// 	// 	// std::cout << "THe value found " << e_position.z << std::endl;
	// 	// }
	// 	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	// 	// {
	// 	// 	e_position.x -= 0.1;
	// 	// }
	// 	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	// 	// {
	// 	// 	e_position.x += 0.1;
	// 	// 	// std::cout << "For x:" << e_position.x << std::endl;
	// 	// }
	// 	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	// 	// {
	// 	// 	std::cout << "For Bot:" << e_position.x << " " << e_position.y << std::endl;
	// 	// }
	}
}
