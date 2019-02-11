#include "Car.hpp"
#include "DEFINITIONS.hpp"


#include <iostream>
#include <cmath>
#include <sstream>

namespace cp
{
	Car::Car(GameDataRef _data, int car_num) : data(_data), car_image_num(car_num) {
		sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		// sprite.scale(3, 3);
		sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - sprite.getGlobalBounds().height * 1.5);
	}
	Car::~Car() {
	}
	void Car::draw_car() {
		data->window.draw(sprite);
	}
}
