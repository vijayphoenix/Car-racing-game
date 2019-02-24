#include "Bot.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>
#include <cmath>
#include <sstream>


namespace cp
{
	Bot::Bot(GameDataRef _data, int car_num)
		:Car(_data, car_num) {
		/////// Setting up entity ////////
		e_speed = sf::Vector3f(0, 0, 200);
		e_max_speed = sf::Vector3f(0, 0, 400);
		///////////////////////////////////
		sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		e_position.x=1.0;
		e_position.z = 4000;
		car_mass = 100;
	}
	Bot::~Bot() {
	}
	void Bot::drawSprite(const Line &line) {
		sf::Sprite &s=sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;
		// std::cout<<"{ Bot:"<<w<<" "<<h<<std::endl;
		// std::cout<<"{Bot::Bot "<<e_position.z<<std::endl;
		// std::cout<<"{Bot::Bot "<<e_position.x<<std::endl;

		/////////// Temp Update //////////////

		float destX = line.X + line.scale * e_position.x * SCREEN_WIDTH / 2;
		float destY = line.Y + 4;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;
		///////// Debug //////////////////
		// /* if(line.W>9000) */std::cout<<"Scale:"<<line.scale<<std::endl;
		// std::cout<<line.W<<" "<<std::endl;

		// std::cout<<"Camera-- Z "<<camera.e_position.z<<" "<<std::endl;
		// std::cout<<"Scale :"<<(camera.camD/(e_position.z - camera.e_position.z))<<" "<<line.scale<<std::endl;


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
		///////// Updating the camera's position ///////////////////
		e_position += e_speed;
		// float speedRatio = e_speed.z / e_max_speed.z; //ASDF
		// float dx = 2 * dt * speedRatio;
		// Line index_line = lines[e_position.z / segL];
		// e_position.x -= (dx * speedRatio * index_line.curve * centrifugal);
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
	}
	void Bot::onCollision(const Car &bot, bool front)
	{

		if (front){
			e_speed.z /= 2;
			std::cout<<"front "<<e_speed.z<<std::endl;
		}
		else{
			e_speed.z += 100;
			std::cout << "back " << e_speed.z << std::endl;
		}
		e_speed.z = std::max(-50.0f, std::min(e_speed.z, e_max_speed.z));
	}
	void Bot::handle_input() {
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		// {
		// 	e_position.z -= 200;
		// }
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		// {
		// 	// std::cout << "initial:" << e_position.z << std::endl;
		// 	e_position.z += 400;
		// 	// std::cout << "THe value found " << e_position.z << std::endl;
		// }
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		// {
		// 	e_position.x -= 0.1;
		// }
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		// {
		// 	e_position.x += 0.1;
		// 	// std::cout << "For x:" << e_position.x << std::endl;
		// }
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		// {
		// 	std::cout << "For Bot:" << e_position.x << " " << e_position.y << std::endl;
		// }
	}

}
