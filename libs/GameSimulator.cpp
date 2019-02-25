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
		fout << "Returning from ~GameSimulator " << std::endl;
	}

	// GameStuff
	void GameSimulator::init() {
		// TODO : Create a helper function to load all the assets required for gamestate
		fout<<"Executing init"<<std::endl;

		/////////////////////
		map.init();
		fout << "Map initialized" <<std::endl;
		/////////////////////

		////////// Loading Car assets ////////////////
		for (int i = 0; i < TOTAL_CARS; i++) {
			resource_store->assets.load_texture("CarImage" + std::to_string(i), CAR_IMAGE_FILEPATH(i));
		}
		fout << "Car Assests Loaded" <<std::endl;
		//////////////////////////////////////////////

		// TODO : Create an object pool
		/////// Creating the main player car and bots
		for (int i = 0; i < TOTAL_BOTS; i++) {
			bot[i] = std::unique_ptr<Bot>(new Bot(resource_store, 5));
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

		// int index = map.get_grid_index(car->e_position.z);
		// Line &temp_line = map.lines[index];
		// car->drawSprite(map.lines[index]);

		resource_store->window.display();
	}
	void GameSimulator::update(float delta) {
		map.bound_entity(main_camera);
		for (int i = 0; i < TOTAL_BOTS; i++) {
			map.bound_entity(*bot[i]);
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
		return resource_store->input.get_mask(id);
	}
}