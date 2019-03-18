#ifndef BULLET_HPP
#define BULLET_HPP

#include "Car.hpp"
#include "Camera.hpp"
#include <vector>

namespace cp
{
class Bullet : public Car
{
  public:
	Bullet(GameDataRef _data, int car_num);
	~Bullet();

	virtual void init(sf::Vector3f pos);
	// virtual void reset();
	void drawSprite(const Line &line);
	virtual void update_car(float dt, const std::vector<Line> &lines, float segL);
	void handle_input();
	int frames=0;
};
} // namespace cp
#endif //BULLET_HPP