#include "States/SplashState.hpp"
#include "States/MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>
#include <sstream>

namespace cp
{
	SplashState::SplashState(GameDataRef _data):data(_data){
	}
	void SplashState::init() {
		data->assets.load_texture("SplashState background",SPLASH_SCENE_BACKGROUND_FILEPATH);
		data->assets.load_font("vfont", "../res/VerminVibesV.otf");
		data->assets.load_font("sfafont", "../res/SFAtarianSystem.ttf");
		background_sprite.setTexture(data->assets.get_texture("SplashState background"));
		background_sprite.scale(1,600.0f/512.0f);
		background_sprite.setPosition(SCREEN_WIDTH / 2 - background_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2.1f - background_sprite.getGlobalBounds().height / 2);
	}
	void SplashState::handle_input(float delta) {
		sf::Event event;
		while(data->window.pollEvent(event))
			if(sf::Event::Closed==event.type)
				data->window.close();
	}
	void SplashState::draw(float delta) {
		data->window.clear();
		data->window.draw(background_sprite);
		data->window.display();
	}
	void SplashState::update(float delta) {
		if(timeover)return;
		if(clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
			std::cout<<"Go to main menu"<<std::endl;
			timeover =true;
			data->machine.add_state(StateRef(new MainMenuState(data)),true);
		}
	}
}
