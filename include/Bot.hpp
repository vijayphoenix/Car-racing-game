#ifndef BOT_HPP
#define BOT_HPP

#include "Car.hpp"

namespace cp
{
	class Bot : public Car
	{
		public:
		Bot					(GameDataRef _data, int car_num);
		~Bot				();

		void 	drawSprite	(Line &line);

		float 	centrifugal = 0.5;
		float 	friction = -max_speed / 5;

		// TODO : Move it to Bot.cpp
		void update_car(float dt, std::vector<Line> &lines, float pos, float segL) {
			// float speedRatio = 1;
			// float dx = 2 * dt * speedRatio;
			// playerX -= lines[position/segL].curve;
			// car_image_num = 5;
		}
		private:
	};
}
#endif //BOT_HPP