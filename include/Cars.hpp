#ifndef CARS_HPP
#define CARS_HPP
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace cp{

	class Cars{

	public:
		Cars(GameDataRef _data,int _car_num);
		// ~Cars();

		void draw_car();

	private:
		GameDataRef data;
		sf::Sprite sprite;
		// float positionX;
	};
}
#endif //CARS_HPP