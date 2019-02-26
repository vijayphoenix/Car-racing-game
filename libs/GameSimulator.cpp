#include "GameSimulator.hpp"

namespace cp {
	GameSimulator::GameSimulator(GameDataRef res_store)
		: resource_store(res_store), fout("GameSimulator.log"), map(res_store) {
		fout<<"Executing GameSimulator "<<std::endl;
		fout<<"Returning from GameSimulator "<<std::endl;
	}
	GameSimulator::~GameSimulator() {
		fout << "Executing ~GameSimulator " << std::endl;
		fout.close();
	}

	// GameStuff
	void GameSimulator::init() {
		fout<<"Executing init"<<std::endl;
		fout << "Assigning id to each bot" << std::endl;
		for (int i = 0; i < TOTAL_BOTS; i++)
		{
			bot_id.push_back(i);
		}
		playerID = 0;
		map.init();
		fout << "Map initialized" <<std::endl;
		/////////////////////

		////////// Loading Car assets ////////////////
		for (int i = 0; i < TOTAL_CARS; i++) {
			resource_store->assets.load_texture("CarImage" + std::to_string(i), CAR_IMAGE_FILEPATH(i));
		}
		fout << "Car Assests Loaded" <<std::endl;
		for (int i = 0; i < TOTAL_BOTS; i++) {
			bot[i] = CarRef(new PlayerCar(resource_store, 5, 0));
			bot[i]->e_position.x = (i & 1) ? 0.0 : -1.1;
			bot[i]->e_position.z = (i / 4) * 4000;
			bot[i]->e_speed.z = 100;
		}
		fout<<"Car and Bots initialized"<<std::endl;
		//////////////////////////////////////////////////

		fout<<"Returning from init"<<std::endl;
	}
	void GameSimulator::handle_input(float delta) {
		sf::Event event;
		while (resource_store->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				resource_store->machine.add_state(StateRef(new GameOverState(resource_store)), true);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				resource_store->machine.remove_state();
			}
		}
		// TODO : Create a driver/bot_mind class
		for (int i = 0; i < TOTAL_BOTS; i++) {
			input_type mask = get_mask(i);

			bot[i]->handle_input(mask, delta);
		}

		main_camera.e_position.x = bot[0]->e_position.x * 1024;
		main_camera.e_position.z = bot[0]->e_position.z - 2000;
	}
	void GameSimulator::draw(float delta) {
		resource_store->window.clear(sf::Color(105, 205, 4));

		map.draw(500, main_camera);

		for (int i = 0; i < TOTAL_BOTS; i++) {
			int index = map.get_grid_index(bot[i]->e_position.z);
			Line &temp_line = map.lines[index];
			bot[i]->drawSprite(map.lines[index]);
		}

		////// Finding camera position and camera height ///
		int startPos = map.get_grid_index(main_camera.getPosition().z);
		///////////////////////////////////////////////////
		for (int n = startPos + 500; n > startPos; n--) {
			drawSprite(map.lines[n % map.getGridCount()]);
			for (int i = 0; i < TOTAL_BOTS; i++)
			{
				int index = (bot[i]->e_position.z) / map.getSegL();
				if (index >= n - 1 and index <= n + 1)
				{
					bot[i]->drawSprite(map.lines[index]);
				}
			}
		}

		resource_store->window.display();
	}
	void GameSimulator::update(float delta) {
		map.bound_entity(main_camera);
		for (int i = 0; i < TOTAL_BOTS; i++) {
			map.bound_entity(bot[i]);
		}

		for (int i = 0; i < TOTAL_BOTS; i++) {

			bot[i]->update_car(delta, map.lines, map.getSegL());
			for (int j = i + 1; j < TOTAL_BOTS; j++) {
				collision.handle_collision(*bot[j], *bot[i], map);
			}
		}
	}
	void GameSimulator::drawSprite(Line &line) {
		sf::Sprite s = line.sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = line.X + line.scale * line.spriteX * map.getScreenWidth() / 2;
		float destY = line.Y + 4;
		float destW = w * line.W / 266;
		float destH = h * line.W / 266;

		destX += destW * line.spriteX; //offsetX
		destY += destH * (-1);		   //offsetY

		float clipH = destY + destH - line.clip;
		if (clipH < 0)
			clipH = 0;
		if (clipH >= destH)
			return;
		s.setTextureRect(sf::IntRect(0, 0, w, h - h * clipH / destH));
		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		resource_store->window.draw(s);
	}


	GameSimulator::input_type GameSimulator::get_mask(int i) {
		ID id = bot_id[i];
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			fout<<"Inputs for player:"<<id<<std::endl;
			for(auto i:resource_store->input.get_mask(id))fout<<i;
			fout<<std::endl;
		}
		return resource_store->input.get_mask(id);
	}
	GameSimulator::input_return_type GameSimulator::get_input() {
		GameSimulator::input_type inputs;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			inputs.push_back(1);
		}
		else inputs.push_back(0);

		return GameSimulator::input_return_type(playerID, inputs);
	}
	GameSimulatorSnap GameSimulator::get_current_snap(SnapFlag flag) {
		if(flag == SnapFlag::NETWORK_SNAP) {
			return GameSimulatorSnap();
		}
	}
}