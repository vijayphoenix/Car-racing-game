#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "NetworkManager.hpp"
#include <iostream>
#include <sstream>

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
	void MainMenuState::handle_input() {
		sf::Event event;
		while(data->window.pollEvent(event)) {
			if(sf::Event::Closed==event.type) {
				data->window.close();
			}
			else if(data->input.is_sprite_clicked(play_button_sprite,sf::Mouse::Left,data->window)){
				std::cout << "Button is pressed" << std::endl;
				//////// The NetworkManager /////
<<<<<<< HEAD
				data->Nmanager.n_thread = std::thread(data->Nmanager.createClient);
				data->Nmanager.n_thread.join();
				// data->Nmanager.createServer();
				//////////// Starting NetworkManager ////////////
				std::cout << "Now starting game loop" << std::endl;
=======
				data->Nmanager.n_thread = std::thread(data->Nmanager.createServer);
				data->Nmanager.n_thread.join();
				//////////// Starting NetworkManager ////////////
				Log("MainMenuState::handle_input", "Pushed game state");
>>>>>>> 14c9370e46fcea7a2e44652a711bfecafecbb722
				/////////////////////////////////
				data->machine.add_state(StateRef(new GameState(data)), true);
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
