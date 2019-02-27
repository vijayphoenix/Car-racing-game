#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "NetworkManager.hpp"
#include <iostream>
#include <sstream>
#include "ServerRoom.hpp"

namespace cp
{
	MainMenuState::MainMenuState(GameDataRef _data):data(_data){
	}
	void MainMenuState::init() {
		data->assets.load_texture("MainMenuStateBackground",MAIN_MENU_BACKGROUND_FILEPATH);
		data->assets.load_texture("PlayButton", PLAY_BUTTON_FILEPATH);
		background_sprite.setTexture(data->assets.get_texture("MainMenuStateBackground"));
		background_sprite.scale(1, 600.0f / 512.0f);
		background_sprite.setPosition(SCREEN_WIDTH / 2 - background_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2.1f - background_sprite.getGlobalBounds().height / 2);
		play_button_sprite.setTexture(data->assets.get_texture("PlayButton"));
		play_button_sprite.scale(Scaling_factor);
		play_button_sprite.setPosition(SCREEN_WIDTH / 2 - play_button_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - play_button_sprite.getGlobalBounds().height / 2);
	}
	void MainMenuState::handle_input(float delta) {
		sf::Event event;
		while(data->window.pollEvent(event)) {
			if(sf::Event::Closed==event.type) {
				data->window.close();
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
				if(server!=true) {
				server = true;
				std::cout << "Adding ServerRoom" << std::endl;
				data->machine.add_state(StateRef(new ServerRoom(data)), false);
				}
			}
		}
	}
	void MainMenuState::draw(float delta) {
		data->window.clear();
		data->window.draw(background_sprite);
		data->window.draw(title_sprite);
		data->window.draw(play_button_sprite);
		data->window.display();
	}
}
