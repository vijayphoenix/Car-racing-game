#include <iostream>
#include <cmath>
#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

namespace cp
{
	GameState::GameState(GameDataRef _data) : data(_data), map(_data){
		network_handle= std::thread(network_handler,data);
	}
	void GameState::init() {

		// TODO : Create a helper function to load all the assets required for gamestate
		map.init();

		////////// Loading Car assets ////////////////
		for(int i = 0; i < TOTAL_CARS; i++)
		{
			data->assets.load_texture("CarImage"+std::to_string(i),CAR_IMAGE_FILEPATH(i));
		}
		//////////////////////////////////////////////

		// TODO : Create an object pool
		/////// Creating the main player car and bots
		car = std::unique_ptr<PlayerCar>(new PlayerCar(data,5,main_camera.getSpeed().z));
		for(int i=0;i<TOTAL_BOTS;i++){
			bot[i] = std::unique_ptr<Bot>(new Bot(data, 5));
		}
		///////////////////////////////////////////////

		////// The Game Begins ///////////////////////
		current_time=clock.getElapsedTime().asSeconds();
		//////////////////////////////////////////////
	}
	void GameState::handle_input() {
		sf::Event event;
		while(data->window.pollEvent(event)) {
			if(sf::Event::Closed==event.type){
				data->window.close();
			}
		}

		new_time=clock.getElapsedTime().asSeconds();

		// TODO : Create a driver/bot_mind class
		for (int i = 0; i < TOTAL_BOTS; i++)
		{
			bot[i]->handle_input();
			// std::cout<<"Bot INfo:"<<bot[i]->e_position.x<<" "<<bot[i]->e_position.y<<" "<<bot[i]->e_position.z<<std::endl;
		}
		car->handle_input();

		main_camera.e_position.x = car->e_position.x*1024;
		main_camera.e_position.z = car->e_position.z - 2000;
		// std::cout<<main_camera.e_position.x<<" "<<main_camera.e_position.y<<" "<<main_camera.e_position.z<<std::endl;

		map.bound_entity(main_camera);
		for (int i = 0; i < TOTAL_BOTS; i++) {
			map.bound_entity(*bot[i]);
		}
		map.bound_entity(car);
		////// The frame Ends ///////////////////////////
		current_time = new_time;
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
		for (int i = 0; i < TOTAL_BOTS; i++)
		{
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
				}
				else if (diff <= 0 and collision.detect_collision(bot[i]->sprite, car->sprite))
				{
					// std::cout << "Collided abck diff:" <<diff<< std::endl;

					car->onCollision(*bot[i], 0);
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

	void GameState::network_handler(GameDataRef game_data){
		sf::Vector3f pos;
		while(game_data->window.isOpen()){
			game_data->Nmanager.receiveData(pos);
		}
	}
}
