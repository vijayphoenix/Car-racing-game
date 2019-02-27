#include <iostream>
#include <cmath>
#include <sstream>
#include "GameOverState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{
	GameState::GameState(GameDataRef _data) : data(_data), map(_data) {
		Log("GameState", "Created a game State");
	}
	void GameState::init() {
		map.init();
		Log("GameState", "Map initialized");

		////////// Loading Car assets ////////////////
		for (int i = 0; i < TOTAL_CARS; i++) {
			data->assets.load_texture("CarImage" + std::to_string(i), CAR_IMAGE_FILEPATH(i));
		}
		Log("GameState", "Car Assests Loaded");
		// player = std::shared_ptr<PlayerCar>(new PlayerCar(data,5,main_camera.getSpeed().z));
		// player->e_position.x = 1.1;

		// for (int i = 0; i < TOTAL_BOTS; i++)
		// {
		// 	bot[i] = CarRef(new PlayerCar(data, 5, main_camera.getSpeed().z));
		// 	bot[i]->e_position.x = (i & 1)?0.0: -1.1;
		// 	bot[i]->e_position.z = (i / 4) * 4000;
		// 	bot[i]->e_speed.z = 100;
		// }
		Log("GameState", "Car and Bots initialized");
		// network_handle = std::thread(network_handler, data, car, bot[0]);
	}
	void GameState::handle_input(float delta) {
		sf::Event event;
		while(data->window.pollEvent(event)) {
			if(sf::Event::Closed==event.type){
				data->machine.add_state(StateRef(new GameOverState(data)), true);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
				data->machine.remove_state();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				data->machine.add_state(StateRef(new PauseState(data)), false);
			}
		}
		std::vector<bool> mask;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mask.push_back(1);
		else
			mask.push_back(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			mask.push_back(1);
		else
			mask.push_back(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			mask.push_back(1);
		else
			mask.push_back(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			mask.push_back(1);
		else
			mask.push_back(0);
		for (int i = 0; i < TOTAL_BOTS; i++) {
			bot[i]->handle_input(mask, delta);
		}

		player->handle_input(mask, delta);
		main_camera.e_position.x = bot[0]->e_position.x * 1024;
		main_camera.e_position.z = bot[0]->e_position.z - 2000;

		// map.bound_entity(main_camera);
		// for (int i = 0; i < TOTAL_BOTS; i++) {
		// 	map.bound_entity(*bot[i]);
		// }
		// map.bound_entity(*player);
	}
	void GameState::draw(float delta){
		data->window.clear(sf::Color(105, 205, 4));

		map.draw(500, main_camera);

		for (int i = 0; i < TOTAL_BOTS; i++) {
			//////////// Temp Update ///////////
			int index = map.get_grid_index(bot[i]->e_position.z);
			Line &temp_line = map.lines[index];
			bot[i]->drawSprite(map.lines[index]);
		}

		////// Finding camera position and camera height ///
		int startPos = map.get_grid_index(main_camera.getPosition().z);
		///////////////////////////////////////////////////
		for (int n = startPos + 500; n >startPos; n--) {
			drawSprite(map.lines[n % map.getGridCount()]);
			for (int i = 0; i < TOTAL_BOTS; i++) {
				int index = (bot[i]->e_position.z)/map.getSegL();
				if (index >= n - 1 and index <= n + 1) {
					bot[i]->drawSprite(map.lines[index]);
				}
			}
		}

		int index = map.get_grid_index(player->e_position.z);
		Line &temp_line = map.lines[index];
		player->drawSprite(map.lines[index]);

		data->window.display();
	}
	void GameState::update(float delta){
		player->update_car(delta,map.lines,map.getSegL());

		for (int i = 0; i < TOTAL_BOTS; i++)
		{
			bot[i]->update_car(delta, map.lines, map.getSegL());

			// collision.handle_collision(*car,*bot[i],map);
			for(int j = i+1; j < TOTAL_BOTS ; j++)
			{
				collision.handle_collision(*bot[j], *bot[i], map);
			}
		}
		// data->Nmanager.sendData(car->e_position);
		// data->Nmanager.sendData(bot[0]->e_position);
	}
	void GameState::drawSprite(Line &line) {
		sf::Sprite s = line.sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * line.spriteX * map.getScreenWidth() / 2;
		float destY = line.Y + 4	;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;

		destX += destW * line.spriteX; //offsetX
		destY += destH * (-1);		   //offsetY

		float clipH = destY + destH - line.clip;
		if (clipH < 0)clipH = 0;
		if (clipH >= destH)	return;
		s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		data->window.draw(s);
	}
	void GameState::network_handler(GameDataRef game_data, std::shared_ptr<PlayerCar> car, std::shared_ptr<Bot> bot) {
		sleep(1);
		sf::Clock clock;
		clock.restart();
		float new_time, frame_time, interpolation;
		float current_time = clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;
		const float delta = 1.0f / 60.0f;
		while(game_data->window.isOpen()) {
			new_time = clock.getElapsedTime().asSeconds();
			frame_time = new_time - current_time;
			if (frame_time > 0.25f)
				frame_time = 0.25f;
			current_time = new_time;
			accumulator += frame_time;

			while (accumulator >= delta)
			{
				std::cout << "Car->Pos:" << car->e_position.x << " " << car->e_position.y << " " << car->e_position.z << std::endl;
				std::cout << "Bot->Pos:" << bot->e_position.x << " " << bot->e_position.y << " " << bot->e_position.z << std::endl;

				game_data->Nmanager.sendData(car->e_position);
				game_data->Nmanager.sendData(bot->e_position);
				accumulator -= delta;
			}
			interpolation = accumulator / delta;
		}
	}
}
