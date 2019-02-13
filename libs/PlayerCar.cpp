#include <iostream>
#include <cmath>
#include <sstream>
#include "PlayerCar.hpp"
#include "DEFINITIONS.hpp"

namespace cp{

	PlayerCar::PlayerCar(GameDataRef _data, int car_num, float &cspeed)
		:Car(_data,car_num),cspeed(cspeed){
		sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
		sprite.scale(3, 3);
		sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT - sprite.getGlobalBounds().height * 1.5);
	}
	PlayerCar::~PlayerCar(){
	}

}