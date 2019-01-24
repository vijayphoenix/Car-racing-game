#include <iostream>
#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{
	SplashState::SplashState(GameDataRef _data):data(_data){}

	void SplashState::init(){
		data->assets.load_texture("SplashState background",SPLASH_SCENE_BACKGROUND_FILEPATH);
		background_sprite.setTexture(data->assets.get_texture("SplashState background"));
		background_sprite.scale(1,600.0f/512.0f);
		background_sprite.setPosition(SCREEN_WIDTH / 2 - background_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2.1f - background_sprite.getGlobalBounds().height / 2);
	}

	void SplashState::handle_input(){
		sf::Event event;
		while(data->window.pollEvent(event))
			if(sf::Event::Closed==event.type)
				data->window.close();
	}

	void SplashState::draw(float delta){
		data->window.clear();
		data->window.draw(background_sprite);
		data->window.display();
	}

	void SplashState::update(float delta){
		if(clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
			std::cout<<"Go to main menu"<<std::endl;
			data->machine.add_state(StateRef(new MainMenuState(data)),true);
		}
	}
}