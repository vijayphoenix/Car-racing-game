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
		PlayerCar		(GameDataRef _data, int _car_num, float cspeed);
		~PlayerCar		();
		void update_car (float dt, const std::vector<Line> & lines, float segL);
		void drawSprite	(const Line &line);
		void drawUsingCamera(const Camera& main_camera);
		float friction 	= e_max_speed.z/5;
		void project(Line &line, float camX, float camY, float camZ, float camD);
		void handle_input(std::vector<bool> mask, float dt);
	};
}
#endif //CARS_HPP


//// TODO: Create a driver class and then use the driver object to finally give
////		a vector to the car for it's movement
// TODO: Choose a better name for this class \//Done