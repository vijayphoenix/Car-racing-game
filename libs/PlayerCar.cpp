#include <iostream>
#include <cmath>
#include <sstream>
#include "PlayerCar.hpp"
#include "DEFINITIONS.hpp"


namespace cp{
	PlayerCar::PlayerCar(GameDataRef _data, int car_num, float cspeed)
		:Car(_data,car_num){
		/////// Setting up entity ////////
		e_speed = sf::Vector3f(0, 0, 0);
		///////////////////////////////////
		sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		e_position.x = 1.0;
		e_position.z = 2000;
		car_mass=100;
		in_use=true;
	}
	PlayerCar::~PlayerCar() {
	}
	void PlayerCar::update_car(const float dt, const std::vector<Line> &lines, const float segL) {
		///////// Updating the camera's position ///////////////////
		// e_position += e_speed;
		float speedRatio = e_speed.z / e_max_speed.z; //ASDF
		float dx = 2 * dt * speedRatio;
		Line index_line = lines[e_position.z / segL];
		e_position.x -= (dx * speedRatio * index_line.curve * centrifugal);
		///////////////////////////////////////////////////

		// e_speed.z = std::max(0.0f, std::min(e_speed.z, e_max_speed.z));
		/////////////////////////////////////////////////////////////////

		/////////// Animating the sprite for the car //////////////////////
		car_image_num = 5;
		if (std::abs(e_speed.z) > 0.1)
		{
			if (l)
				car_image_num = 3;
			else if (r)
				car_image_num = 4;
			sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		}
		/////////////////////////////////////////////////////////////////////
		// e_position.z += e_speed.z;
		// e_position.y = index_line.y;
		// std::cout << "PlayerCar::update_car " << e_position.y << " " << index_line.y << std::endl;
	}
	void PlayerCar::drawSprite(const Line &line) {
		sf::Sprite &s = sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * e_position.x * SCREEN_WIDTH / 2;
		float destY = line.Y + 4;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;
		destX += destW * e_position.x; //offsetX
		destY -= destH;				   //offsetY

		float clipH = destY + destH - line.clip;
		if (clipH < 0)
			clipH = 0;
		if (clipH >= destH)
			return;

		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		data->window.draw(s);
	}

	void PlayerCar::handle_input(float dt) {
		float speedRatio = e_speed.z / e_max_speed.z;
		float dx = 2 * dt * speedRatio;
		l=r =false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			e_speed.z += e_acceleration.z * dt;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			e_speed.z += e_decleration.z * dt;
		}
		// else
		// {
		// 	if(speedRatio>0)e_speed.z += friction * dt;
		// }
		e_speed.z = std::max(-50.0f, std::min(e_speed.z, e_max_speed.z));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			e_position.x -= dx;
			l = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			e_position.x += dx;
			r = true;
		}
		e_position+=e_speed;
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		// {
		// 	e_position.z -= e_speed.z;
		// }
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		// {
		// 	// std::cout << "initial:" << e_position.z << std::endl;
		// 	e_position.z += e_speed.z;
		// 	// std::cout<<"E_SEPP:"<<e_speed.z<<std::endl;
		// 	// std::cout << "THe value found " << e_position.z << std::endl;
		// }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			std::cout << "For Bot:" << e_position.x << " " << e_position.y << std::endl;
		}
	}
}