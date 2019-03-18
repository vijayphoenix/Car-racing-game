#ifndef CARS_HPP
#define CARS_HPP
#include <iostream>
#include "Car.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Camera.hpp"


namespace cp{
	class PlayerCar : public Car{
		public:
		PlayerCar		(GameDataRef _data, int _car_num);
		~PlayerCar		();
		void update_car (float dt, const std::vector<Line> & lines, float segL);
		void drawSprite	(const Line &line);
		void drawUsingCamera(const Camera& main_camera);
		float friction 	= e_max_speed.z/5;
		void project(Line &line, float camX, float camY, float camZ, float camD);
		void handle_input(std::vector<bool> mask, float dt);
		int img=1;
	};
}
#endif //CARS_HPP
