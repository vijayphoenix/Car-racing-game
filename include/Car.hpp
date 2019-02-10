#ifndef CAR_HPP
#define CAR_HPP

#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Line.hpp"
#include <vector>

namespace cp{

	class Car{

	public:
	  Car(GameDataRef _data, int car_num);
	  ~Car();

	  void draw_car();
	  virtual void update_car(float dt,std::vector<Line> &lines, float pos, float segL)= 0;


	  // float centrifugal = 0.5;
	  // float friction = -max_speed / 5;
	  float playerX = 0;
	  float speed = 0;
	  float position = 0;
	  float max_speed = 400;
	  float acceleration = max_speed / 5;
	  float decleration = -max_speed;

	  int car_image_num;
	  sf::Sprite sprite;
	  GameDataRef data;

	private:
	};
}
#endif //CAR_HPP