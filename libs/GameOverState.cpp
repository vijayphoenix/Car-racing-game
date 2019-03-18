#include "States/GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <sstream>

namespace cp
{
	GameOverState::GameOverState(GameDataRef _data):data(_data){
	}
	void GameOverState::init() {
		data->assets.load_texture("GameOverState background",GAME_OVER_BACKGROUND_FILEPATH);
		font=data->assets.get_font("sfafont");
		text.setFont(font);
		text.setString("Credits: \n\n Vijay Tadikamalla \n\n Anupam Saini\n\n Anjani kumar \n\n Yogesh Singh");
		text.setPosition(SCREEN_WIDTH/3,SCREEN_HEIGHT/4);
		text.setCharacterSize(56);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setOutlineColor(sf::Color::White);
		text.setOutlineThickness(2);
	}
	void GameOverState::handle_input(float delta)
	{
		sf::Event event;
		while(data->window.pollEvent(event))
			if(sf::Event::Closed==event.type)
				data->window.close();
	}
	void GameOverState::draw(float delta) {
		data->window.clear();
		data->window.draw(text);
		data->window.display();
	}
	void GameOverState::update(float delta) {
		if (clock.getElapsedTime().asSeconds() > 3 )
		{
			std::cout << "Exiting" << std::endl;
			data->window.close();
		}
	}
}
