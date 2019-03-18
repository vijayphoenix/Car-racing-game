#ifndef BOT_HPP
#define BOT_HPP

#include "Car.hpp"
#include "Camera.hpp"
#include <vector>

namespace cp
{
	class Bot : public Car
	{
		public:
		using input_type = std::vector<bool>;

		Bot(GameDataRef _data, int car_num);
		~Bot();

		void drawSprite(const Line &line);
		virtual void update_car(float dt, const std::vector<Line> &lines, float segL);
		void handle_input(input_type mask, float dt);
		void handle_input();
		int img = 1;
	};
}
#endif //BOT_HPP