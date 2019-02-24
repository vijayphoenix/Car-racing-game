#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>
#include <sstream>

namespace cp
{
	GameOverState::GameOverState(GameDataRef _data):data(_data){
	}
	void GameOverState::init() {
		data->assets.load_texture("GameOverState background",GAME_OVER_BACKGROUND_FILEPATH);
		background_sprite.setTexture(data->assets.get_texture("GameOverState background"));
		background_sprite.scale(Scaling_factor);
	}
	void GameOverState::handle_input() {
		sf::Event event;
		while(data->window.pollEvent(event))
			if(sf::Event::Closed==event.type)
				data->window.close();
	}
	void GameOverState::draw(float delta) {
		data->window.clear();
		data->window.draw(background_sprite);
		data->window.display();
	}
	void GameOverState::update(float delta) {
	}
}
