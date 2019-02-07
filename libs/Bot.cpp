#include <iostream>
#include <cmath>
#include <sstream>
#include "Bot.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{

Bot::Bot(GameDataRef _data, int car_num, float position)
	:Car(_data, car_num)
{
	speed = 200;
	sprite.setTexture(data->assets.get_texture("CarImage" + std::to_string(car_image_num)));
	sprite.scale(3, 3);
	sprite.setPosition(SCREEN_WIDTH / 2 - sprite.getGlobalBounds().width/2, SCREEN_HEIGHT - sprite.getGlobalBounds().height * 1.5);
}


Bot::~Bot()
{
}

void Bot::drawSprite(Line &line)
{
	// s = line.sprite;
	sf::Sprite s=sprite;
	int w = s.getTextureRect().width;
	int h = s.getTextureRect().height;

	float destX = line.X + line.scale * (-2) * SCREEN_WIDTH / 2;
	float destY = line.Y + 4;
	float destW = w * line.W / 266;
	float destH = h * line.W / 266;

	destX += destW * -2; //offsetX
	destY += destH * (-1);		   //offsetY

	float clipH = destY + destH - line.clip;
	if (clipH < 0)
		clipH = 0;
	if (clipH >= destH)
		return;
	s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
	s.setScale(destW / w, destH / h);
	s.setPosition(destX, destY);
	data->window.draw(s);
}

} // namespace cp