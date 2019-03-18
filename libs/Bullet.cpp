#include "Objects/Bullet.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <cmath>
#include <sstream>

namespace cp
{
Bullet::Bullet(GameDataRef _data, int car_num): Car(_data, car_num)
{
	/////// Setting up entity ////////

	e_speed = sf::Vector3f(0, 0, 600);
	e_max_speed = sf::Vector3f(0, 0, 600);
	health=0.1;
	///////////////////////////////////
	sprite.setTexture(data->assets.get_texture("Bullet"));
	sprite.scale(0.01,0.01);
}
Bullet::~Bullet()
{
}

void Bullet::init(sf::Vector3f pos)
{
	in_use=true;
	frames=0;
	e_speed = sf::Vector3f(0, 0, 600);
	e_position=pos;
}

void Bullet::drawSprite(const Line &line)
{
	if(!in_use)return;
	sf::Sprite &s = sprite;

	int w = s.getTextureRect().width;
	int h = s.getTextureRect().height;
	// std::cout<<"{ Bullet:"<<w<<" "<<h<<std::endl;
	// std::cout<<"{Bullet::Bullet "<<e_position.z<<std::endl;
	// std::cout<<"{Bullet::Bullet "<<e_position.x<<std::endl;

	/////////// Temp Update //////////////

	float destX = line.no_curve_X + line.scale * e_position.x * SCREEN_WIDTH / 2;
	// if(line.no_curve_Y<line.Y)return;
	float destY = line.no_curve_Y + 4;
	float destW = w * line.W / 266;
	float destH = h * line.W / 266;
	///////// Debug //////////////////
	// /* if(line.W>9000) */std::cout<<"Scale:"<<line.scale<<std::endl;
	// std::cout<<line.W<<" "<<std::endl;

	// std::cout<<"Camera-- Z "<<camera.e_position.z<<" "<<std::endl;
	// std::cout<<"Scale :"<<(camera.camD/(e_position.z - camera.e_position.z))<<" "<<line.scale<<std::endl;

	destX += destW * e_position.x; //offsetX
	destY -= destH;				   //offsetY

	float clipH = destY + destH - line.clip;
	if (clipH < 0)
		clipH = 0;
	if (clipH >=destH)
		return;

	s.setScale(destW / w, destH / h);
	s.setPosition(destX, destY);
	data->window.draw(s);
}
void Bullet::update_car(const float dt, const std::vector<Line> &lines, const float segL)
{
	frames++;
	if(frames>30)in_use=false;
	if (!in_use)return;
	e_position.z += e_speed.z;
	// float speedRatio = e_speed.z / e_max_speed.z; //ASDF
	// float dx = 2 * dt * speedRatio;
	// Line index_line = lines[e_position.z / segL];
	// e_position.x -= (/* dx * speedRatio *  */index_line.curve * centrifugal);
	// std::cout<<e_position.x<<std::endl;
}
void Bullet::handle_input()
{
}

} // namespace cp
