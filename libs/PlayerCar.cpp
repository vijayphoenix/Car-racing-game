/**
 * @file PlayerCar.cpp
 * @author Vijay
 * @brief PlayerCar.cpp provides Car object
 * @version 0.1
 * @date 2019-03-01
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <iostream>
#include <cmath>
#include <time.h>
#include <sstream>
#include "Objects/PlayerCar.hpp"
#include "DEFINITIONS.hpp"
#include "fstream"

namespace cp{
	/**
	 * @brief Construct a new Player Car:: Player Car object
	 *
	 * @param _data Pointer Reference to the resources and state machines.
	 * @param car_num The sprite number for the car object
	 */
	PlayerCar::PlayerCar(GameDataRef _data, int car_num)
		:Car(_data,car_num){
		/////// Setting up entity ////////
		e_speed = sf::Vector3f(0, 0, rand()%20);
		///////////////////////////////////
		sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		e_position.x = -2+rand()%4;
		e_position.z = 10000+rand()%10000;
		if (car_image_num == 8)
		{
			health = 50;
			e_max_speed.z = 250;
		}
		// else health = 100000;
		car_mass=100;
		in_use=true;
	}

	/**
	 * @brief Destroy the Player Car:: Player Car object
	 *
	 */
	PlayerCar::~PlayerCar() {
	}

	/**
	 * @brief Update the car according to it's position and the map
	 *
	 * @param dt Time difference between two update frames
	 * @param lines provides the map grid info
	 * @param segL Segment line between two grid in the map
	 */
	void PlayerCar::update_car(const float dt, const std::vector<Line> &lines, const float segL) {
		///////// Updating the camera's position ///////////////////
		float speedRatio = std::abs(e_speed.z / e_max_speed.z); //ASDF
		float dx = 3 * dt * speedRatio;
		Line index_line = lines[e_position.z / segL];
		e_position.x -= (dx * speedRatio * index_line.curve * centrifugal);
		e_position.x = std::max(-1.0f, std::min(e_position.x, 1.0f));

	}

	/**
	 * @brief Utility function to draw sprites of the car.
	 *
	 * @param line Provides info regarding map scale at the current grid the car is positioned at
	 */
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

	/**
	 * @brief Provides interface to control the car
	 *
	 * @param mask Boolean mask indicating the Keyboard inputs.
	 * @param dt Time difference between two handle_input call.
	 */
	void PlayerCar::handle_input(std::vector<bool> mask, float dt) {
		float speedRatio = std::abs(e_speed.z / e_max_speed.z);
		float dx = 5 * dt * speedRatio;
		if (mask[0]) {
			e_speed.z += e_speed.z == 0 ? 15 : (e_acceleration.z * dt);
		}
		else if (mask[1]) {
			e_speed.z += ( e_speed.z > 15 || e_speed.z < -15 ) ? e_decleration.z * dt : (e_speed.z > 0 ? -e_speed.z : -15);
		}
		e_speed.z -= std::abs(e_speed.z) < 15 ? e_speed.z : (e_speed.z / 250);
		e_speed.z = std::max(-100.0f, std::min(e_speed.z, e_max_speed.z));
		if (mask[2])e_position.x -= dx;
		else if (mask[3])e_position.x += dx;
		e_position += e_speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			std::cout << "For Bot:" << e_position.x << " " << e_position.y << std::endl;
		}
		e_position.x = std::max(-4.0f, std::min(e_position.x, 3.0f));
		if (health <= 0 and car_image_num==8)
		{
			sprite.setTexture(data->assets.get_texture("f" + std::to_string((int)std::ceil(((float)(img++)) / 4))));
			if (img >= 48)
			{
				*this = PlayerCar(data, this->car_image_num);
				img = 1;
			}
		}
		if (std::abs(e_speed.z) > 0.1)
		{
			if (mask[2])
				sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num - 2)));
			else if (mask[3])
				sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num - 1)));
			else
				sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		}

	}
}