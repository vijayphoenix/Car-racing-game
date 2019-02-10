#include <iostream>
#include <cmath>
#include <sstream>
#include "Bot.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{

Bot::Bot(GameDataRef _data, int car_num)
	:Car(_data, car_num)
{
	speed = 200;
	sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
	// sprite.scale(3, 3);
	// sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width/2, SCREEN_HEIGHT - sprite.getGlobalBounds().height * 1.5);
}


Bot::~Bot()
{
}

void Bot::drawSprite(Line &line)
{
	// s = line.sprite;
	sf::Sprite &s=sprite;
	int SpriteX= -2.5;
	int w = s.getTextureRect().width;
	int h = s.getTextureRect().height;
	// h*=2;
	// if(abs(num)<8)return;

	float destX = line.X + line.scale * SpriteX * SCREEN_WIDTH / 2;
	float destY = line.Y + 4;
	if (destY > SCREEN_HEIGHT) return;
	float destW = w * line.W / 266;
	float destH = h * line.W / 266;

	destX += destW * SpriteX;	  //offsetX
	destY -= destH;		   //offsetY

	// std::cout <<destX <<"=destx" << std::endl;
	// std::cout <<destY <<"=desty" << std::endl;
	// std::cout <<destH <<"=desth" << std::endl;
	// std::cout << destW << "=destw" << std::endl;
	// std::cout << w<<"=w" << std::endl;
	// std::cout << h << "=h" << std::endl;


	float clipH = destY + destH - line.clip;
	if (clipH < 0)	clipH = 0;
	if (clipH >=destH)return;
	// float d = 1.1;
	// std::cout << "{ " << destW / w << " " << destH / h << std::endl;
	// if (destW / w > d || destH / h > d)
	// {
	// 	destW = w;
	// 	destH = h;
	// }
	// s.setTextureRect(sf::IntRect(0, 0, w,h /* - h * clipH / destH */));
		// std::cout<<"hi";
	// if (destY + sprite.getGlobalBounds().height < SCREEN_HEIGHT)
	// if (destW<=300 and destH<=300)
		s.setScale(destW / w, destH / h);
	// }
	// else
	// {
	// 	s.setScale(3, 3);
	// 	// s.setPosition(, 0);
	// }
		s.setPosition(destX, destY);

	// std::cout << destW << " =destw " << destH<<" =desth"<< std::endl;
	// std::cout << w << " =w " << h << " =h" << std::endl;

	data->window.draw(s);
}

} // namespace cp