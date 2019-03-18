#ifndef PERCENTAGEBAR_HPP
#define PERCENTAGEBAR_HPP

#include<SFML/Graphics.hpp>
#include"Game.hpp"

namespace cp{

	class PercentageBar{

	public:
		float percentage = 100;
		PercentageBar(GameDataRef _data):data(_data){
		}
		// ~PercentageBar();
		void init(sf::Vector2f size,sf::Vector2f position,sf::Color c1,sf::Color c2){
			rect1.setPosition(position);
			rect1.setSize(size);
			rect1.setFillColor(sf::Color(0,0,0,150));
			rect1.setOutlineColor(c1);
			rect1.setOutlineThickness(3);
			rect2.setPosition(position);
			rect2.setSize(size);
			rect2.setFillColor(sf::Color::Green);
		}

		void draw(){
			if(percentage>=0)rect2.setScale(percentage/100,1);
			else percentage=0;
			if(percentage > 75)
				rect2.setFillColor(sf::Color::Green);
			else if(percentage > 50 && percentage <=75)
				rect2.setFillColor(sf::Color(103, 255, 153));
			else if (percentage > 25 && percentage <= 50)
				rect2.setFillColor(sf::Color(255, 102, 102));
			else if (percentage > 0 && percentage <= 25)
				rect2.setFillColor(sf::Color::Red);
			data->window.draw(rect1);
			data->window.draw(rect2);
		}


	private:
		GameDataRef data;
		sf::RectangleShape rect1,rect2;
	};
}
#endif //PERCENTAGEBAR_HPP