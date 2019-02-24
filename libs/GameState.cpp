#include <iostream>
#include <cmath>
#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{
	GameState::GameState(GameDataRef _data) : data(_data), map(_data) {
		Log("GameState", "Created a game State");
	}
	void GameState::init() {

		// TODO : Create a helper function to load all the assets required for gamestate

		map.init();
		Log("GameState", "Map initialized");

		////////// Loading Car assets ////////////////
		for(int i = 0; i < TOTAL_CARS; i++)
		{
			data->assets.load_texture("CarImage"+std::to_string(i),CAR_IMAGE_FILEPATH(i));
		}
		Log("GameState", "Car Assests Loaded");

		//////////////////////////////////////////////

		// TODO : Create an object pool
		/////// Creating the main player car and bots
		car = std::shared_ptr<PlayerCar>(new PlayerCar(data,5,main_camera.getSpeed().z));
		for(int i=0;i<TOTAL_BOTS;i++){
			bot[i] = std::unique_ptr<Bot>(new Bot(data, 5));
		}
		Log("GameState", "Car and Bots initialized");

		///////////////////////////////////////////////

		////// The Game Begins ///////////////////////
		// current_time=clock.getElapsedTime().asSeconds();
		//////////////////////////////////////////////
		// network_handle = std::thread(network_handler, data, car, bot[0]);
		// Log("GameState", "Network handle initialized");
	}
	void GameState::handle_input(float delta) {
		sf::Event event;
		while(data->window.pollEvent(event)) {
			if(sf::Event::Closed==event.type){
				data->window.close();
			}
		}

		// new_time=clock.getElapsedTime().asSeconds();

		// TODO : Create a driver/bot_mind class
		for (int i = 0; i < TOTAL_BOTS; i++)
		{
			bot[i]->handle_input();
			// std::cout<<"Bot INfo:"<<bot[i]->e_position.x<<" "<<bot[i]->e_position.y<<" "<<bot[i]->e_position.z<<std::endl;
		}
		car->handle_input(delta);

		main_camera.e_position.x = car->e_position.x*1024;
		main_camera.e_position.z = car->e_position.z - 2000;
		// std::cout<<main_camera.e_position.x<<" "<<main_camera.e_position.y<<" "<<main_camera.e_position.z<<std::endl;

		map.bound_entity(main_camera);
		for (int i = 0; i < TOTAL_BOTS; i++) {
			map.bound_entity(*bot[i]);
		}
		map.bound_entity(car);
		////// The frame Ends ///////////////////////////
		// current_time = new_time;
		////////////////////////////////////////////////
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

		int index = map.get_grid_index(car->e_position.z);
		Line &temp_line = map.lines[index];
		car->drawSprite(map.lines[index]);

		data->window.display();
	}
	void GameState::update(float delta){
		car->update_car(delta,map.lines,map.getSegL());

		for (int i = 0; i < TOTAL_BOTS; i++)
		{
			bot[i]->update_car(delta, map.lines, map.getSegL());

			int index = map.get_grid_index(bot[i]->e_position.z);
			int diff = index % map.getGridCount() - map.get_grid_index(car->e_position.z) % map.getGridCount();

			// std::cout<<"GameState::Update"<<std::endl;
			// std::cout<<diff<<std::endl;
			if (std::abs(diff) <= 4)
			{
				if (diff > 0 and collision.detect_collision(car->sprite, bot[i]->sprite))
				{
					// std::cout<<"Collided Front diff:"<<diff<<std::endl;
					car->onCollision(*bot[i], 1);
					bot[i]->onCollision(*car, 0);
				}
				else if (diff <= 0 and collision.detect_collision(bot[i]->sprite, car->sprite))
				{
					// std::cout << "Collided abck diff:" <<diff<< std::endl;

					car->onCollision(*bot[i], 0);
					bot[i]->onCollision(*car, 1);
				}
				// else std::cout<<"Near but no coll"<<std::endl;
			}
			// else std::cout<<"No coli diff:"<<diff<<std::endl;
		}
	}
	void GameState::drawSprite(Line &line) {
		s = line.sprite;
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
