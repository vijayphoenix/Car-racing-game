#include <iostream>
#include <cmath>
#include <sstream>
#include "Car.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{

Car::Car(GameDataRef _data, int car_num) : data(_data), car_image_num(car_num)
{
	sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
	// sprite.scale(3, 3);
	sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - sprite.getGlobalBounds().height * 1.5);
}

Car::~Car()
{

}

void Car::draw_car()
{
	data->window.draw(sprite);
}

// void Car::update_car(float &speed, float dt, float &playerX, std::vector<Line> &Lines,float pos, float segL){
	// std::cout<<dt<<std::endl;
	// float speedRatio = speed / max_speed;
	// float dx = 2 * dt * speedRatio;
	// bool l = false, r = false;
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	// {
	// 	playerX -= dx;
	// 	l = true;
	// }
	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	// {
	// 	playerX += dx;
	// 	r = true;
	// }

	// playerX -= (dx * speedRatio * curve * centrifugal);

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	// {
	// 	speed += acceleration * dt;
	// }
	// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	// 	speed += decleration * dt;
	// else
	// 	speed += friction * dt;
	// // playerX=std::max(-2.0f,std::min(playerX,2.0f));
	// speed = std::max(0.0f, std::min(speed, max_speed));
	// car_image_num = 5;
	// if (speed > 0.1)
	// {
	// 	if (l)
	// 		car_image_num = 3;
	// 	else if (r)
	// 		car_image_num = 4;
	// 	sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
	// 	sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - sprite.getGlobalBounds().height * (1.5 + 2 * speedRatio * speedRatio));
	// 	sprite.setScale(3 - speedRatio * speedRatio, 3 - speedRatio * speedRatio);
	// }
// }

} // namespace cp