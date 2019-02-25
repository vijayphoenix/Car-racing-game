#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <sstream>

namespace cp
{
	GameOverState::GameOverState(GameDataRef _data):data(_data){
	}
	void GameOverState::init() {
		data->assets.load_texture("GameOverState background",GAME_OVER_BACKGROUND_FILEPATH);
		font=data->assets.get_font("vfont");
		text.setFont(font);
		text.setString("Credits: \n\n   Vijay Tadikamalla\n\n  Anjani kumar");
		text.setPosition(SCREEN_WIDTH/3,SCREEN_HEIGHT/3);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setOutlineColor(sf::Color::White);
		text.setOutlineThickness(2);
		background_sprite.setTexture(data->assets.get_texture("GameOverState background"));
		background_sprite.scale(Scaling_factor);
		// data->window.draw(text);
		// data->window.display();
		// data->window.draw(text);
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
		// data->window.draw(background_sprite);
		data->window.draw(text);
		data->window.display();
	}
	void GameOverState::update(float delta) {
		if (clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			std::cout << "Exiting" << std::endl;
			data->window.close();
		}
	}
}
