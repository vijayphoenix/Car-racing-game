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
		init_car_res();
		fout << "Car Assests Loaded" <<std::endl;
		for (int i = 0; i < TOTAL_BOTS; i++) {
			add_bot_players();
		}
		bot_inp_reg();
		map.init();
		fout << "Map initialized" <<std::endl;
		fout<<"Car and Bots initialized"<<std::endl;
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
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
				generate_log();
			}
		}

		update_controllable(delta);

	}
	void GameSimulator::draw(float delta) {
		resource_store->window.clear(sf::Color(105, 205, 4));
		if(!is_main_player_available())return;

		map.draw(500, main_camera);

		draw_all_players();

		////// Finding camera position and camera height ///
		int startPos = map.get_grid_index(main_camera.getPosition().z);
		///////////////////////////////////////////////////
		for (int n = startPos + 500; n > startPos; n--) {
			drawSprite(map.lines[n % map.getGridCount()]);
			for(auto &player_i:players_map) {
				int index = map.get_grid_index(player_i.second.getPosition().z) ;
				if (index >= n - 1 and index <= n + 1)
					draw_player(player_i.second);
			}
		}

		resource_store->window.display();
	}
	void GameSimulator::update(float delta) {
		focus_on(main_player_id);
		map.bound_entity(main_camera);
		for(auto &player_i:players_map) {
			map.bound_entity(player_i.second);
		}
		// for (int i = 0; i < TOTAL_BOTS; i++) {
		// 	bot[i]->update_car(delta, map.lines, map.getSegL());
		// 	for (int j = i + 1; j < TOTAL_BOTS; j++) {
		// 		collision.handle_collision(*bot[j], *bot[i], map);
		// 	}
		// }
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

	GameSimulatorSnap GameSimulator::get_current_snap(SnapFlag flag) {
		if(flag == SnapFlag::NETWORK_SNAP) {
			// fout << "Requeusted a NETWORK_SNAP"s << std::endl;
			return GameSimulatorSnap();
		}
		if(flag == SnapFlag::OFFLINE_SNAP) {
			fout<<"Requeusted a OFFLINE_SNAP"<<std::endl;
			return GameSimulatorSnap(
				ext_players_count, bot_players_count, MAX_EXT_ALLOWED, main_player_id, players_map);
		}
	}
}