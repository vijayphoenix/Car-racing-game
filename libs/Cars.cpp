#include <iostream>
#include <cmath>
#include <sstream>
#include "Cars.hpp"
#include "DEFINITIONS.hpp"

namespace cp{

	Cars::Cars(GameDataRef _data,int car_num):data(_data){
		sprite.setTexture(data->assets.get_texture("CarImage"+std::to_string(car_num)));
		sprite.scale(0.1,0.1);
		sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT/2);
	}

	void Cars::draw_car(){
		// std::cout<<"hkahla";
		data->window.draw(sprite);
	}

}