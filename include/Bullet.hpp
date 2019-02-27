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
	Bullet(GameDataRef _data, int car_num,sf::Vector3f pos);
	~Bullet();

	void drawSprite(const Line &line);
	virtual void update_car(float dt, const std::vector<Line> &lines, float segL);
	void handle_input();
	void project(Line &line, float camX, float camY, float camZ, float camD)
	{
		line.scale = camD / (line.z - camZ);

		// If line.scale > 1 (threshold ) then the line is between the camera and the projection plane
		// So it is not visible on the screen and hence no need to over scale it.
		// if(line.scale>0.049 || line.scale<0)line.scale = 0.049;
		////////////////////////////////////////////////////////////////////////////////////

		line.X = (1 + line.scale * (line.x - camX)) * SCREEN_WIDTH / 2;
		line.Y = (1 - line.scale * (line.y - camY)) * SCREEN_HEIGHT / 2;
		line.W = line.scale * 2000 * SCREEN_WIDTH / 2;
	}
};
} // namespace cp
#endif //BULLET_HPP