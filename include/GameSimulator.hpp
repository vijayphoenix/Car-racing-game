/**
 * @file GameSimulator.hpp
 * @author Anjani Kumar (cs17btech11002@iith.ac.in)
 * @brief A game simulator just like Game class but it get's its clock sync
 * and resource manager from object owner.
 * @version 0.1
 * @date 2019-02-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef GAME_SIMULATOR_HPP
#define GAME_SIMULATOR_HPP
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "Bot.hpp"
#include "PlayerCar.hpp"
#include "Line.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "GameMap.hpp"
#include <memory>
#include <fstream>

namespace cp {
	class entity_info {
		float x, y, z;
		float speed_x, speed_y, speed_z;
		public:
		entity_info(cp::PlayerCar &car) {
			x = car.getPosition().x;
			y = car.getPosition().y;
			z = car.getPosition().z;
			speed_x = car.getSpeed().x;
			speed_y = car.getSpeed().y;
			speed_z = car.getSpeed().z;
		}
		friend std::ofstream& operator<<(std::ofstream& fout, const entity_info& entity_i) {
			fout << "Position:" << entity_i.x << " " << entity_i.y << " " << entity_i.z << std::endl;
			fout << "Speed   :" << entity_i.speed_x << " " << entity_i.speed_y << " " << entity_i.speed_z << std::endl;
			return fout;
		}
	};
	enum class SnapFlag {
		NETWORK_SNAP,
		OFFLINE_SNAP
	};
	class GameSimulatorSnap {
		private:
		using ID = long long int;
		int ext_players_count;
		int bot_players_count;
		int MAX_EXT_ALLOWED;
		ID main_player_id;
		std::map<ID, entity_info> data;

		public:
		GameSimulatorSnap(){}
		GameSimulatorSnap(int a, int b, int c, int d, std::map<ID, PlayerCar> &players_map) {
			ext_players_count = a;
			bot_players_count = b;
			MAX_EXT_ALLOWED = c;
			main_player_id = d;
			data.clear();
			for (auto &player : players_map) {
				data.insert(std::pair<ID, entity_info>(player.first, entity_info(player.second)));
			}
		}
		friend std::ofstream& operator<<(std::ofstream& fout, const GameSimulatorSnap& snap) {
			fout << "\n\n/***" << std::endl;
			fout << "Total_external_players:" << snap.ext_players_count << std::endl;
			fout << "Total_bot_players:" << snap.bot_players_count << std::endl;
			fout << "MAX_external_players_ALLOWED:" << snap.MAX_EXT_ALLOWED << std::endl;
			fout << "Current Main Player:" << snap.main_player_id << std::endl;
			fout << "These are the players:" << std::endl;
			for (auto &player_i : snap.data){
				fout<<"Data Related to player:"<<player_i.first<<std::endl;
				fout<<player_i.second;
			}
			return fout;
		}
	};
	class GameSimulationLog {
	};

	class GameSimulator {
		// Stuff for handling simulation usage.
		public:
		using ID = long long int;
		using input_type = Bot::input_type;
		using input_return_type = std::pair<ID, input_type>;
		private:

		/**
		 * @brief resource_store proivdes assets, inputs, drawing window.
		 *
		 */
		GameDataRef resource_store;

		public:
		GameSimulator(GameDataRef res_store);
		~GameSimulator();

		/**
		 * @brief Get the current snap object
		 *
		 * @param flag
		 * @return GameSimulatorSnap
		 */
		GameSimulatorSnap get_current_snap(SnapFlag flag);

		/**
		 * @brief Updates the game simulation with the snap provided.
		 *
		 * @param snap Refers to the snap of the game to update the simulation with.
		 * @param is_forced If set then forcefully overwrites the snap provided.
		 * @return GameSimulationLog Returns a log describing whether the replacment was partial/discarded/sucess.
		 */
		GameSimulationLog use_snap(const GameSimulatorSnap &snap, bool is_forced = true);

		// Stuffs for getting logs
		std::ofstream fout;
		void generate_log() {
			fout<<get_current_snap(SnapFlag::OFFLINE_SNAP);
		}


		// Game Stuff
		public:
		void init();
		void handle_input(float delta);
		void draw(float delta);
		void update(float delta);

		private:
		// All the game Entities
		using CarRef = std::shared_ptr<PlayerCar>;


		GameMap map;
		void drawSprite(Line &line);

		// All related to players
		// Server Side
		int ext_players_count = 0;
		int bot_players_count = 0;
		int MAX_EXT_ALLOWED = 4;
		std::map<ID, PlayerCar> players_map;
		ID main_player_id = -1;
		public:
		/**
		 * @brief Adds external player with their id
		 *
		 * @param id This is the id they have requested.
		 * @return true if player addition is successful
		 * @return false if player addition fails
		 */
		bool add_external_player(ID id) {
			if(ext_players_count>=MAX_EXT_ALLOWED)return false;
			if(players_map.find(id)!=players_map.end())return false;
			fout<<"Adding a player with id:"<<id<<std::endl;
			players_map.insert(std::pair<ID, PlayerCar>(id, PlayerCar(resource_store, 5)));
			ext_players_count++;
			return true;
		}
		/**
		 * @brief Adds a bot player in the simulation.
		 *
		 * @return true Returns true if bot addition was a success.
		 * @return false Returns false otherwise.
		 */
		bool add_bot_players() {
			players_map.insert(std::pair<ID, PlayerCar>(-1*bot_players_count-1, PlayerCar(resource_store, 5)));
			bot_players_count++;
			return true;
		}
		/**
		 * @brief Removes an external player if available.
		 *
		 * @param id Id of the external player to remove.
		 */
		void remove_ext_player(ID id) {
			if(players_map.find(id)!= players_map.end()) {
				players_map.erase(id);
				ext_players_count--;
			}
		}
		/**
		 * @brief Update the main player of the simulation.
		 *
		 * @param id Update the main player with ID
		 * @return true If operation is succesfull.
		 * @return false If operation is unsuccessfull.
		 */
		bool update_main_player(ID id) {
			if(players_map.find(id)!=players_map.end()) {
				main_player_id = id;
				return true;
			}
			return false;
		}
		/**
		 * @brief Checks if main player is in the simulation.
		 *
		 * @return true if main player is found.
		 * @return false if main player not found.
		 */
		bool is_main_player_available() {
			if(players_map.find(main_player_id)!=players_map.end())return true;
			else return false;
		}
		private:
		/**
		 * @brief Initialize car resources
		 *
		 */
		void init_car_res() {
			for (int i = 0; i < TOTAL_CARS; i++) {
				resource_store->assets.load_texture("CarImage" + std::to_string(i), CAR_IMAGE_FILEPATH(i));
			}
		}
		/**
		 * @brief Update all the controllable entities.
		 *
		 */
		void update_controllable(float delta) {
			for(auto &player:players_map) {
				input_type mask = get_mask(player.first);
				player.second.handle_input(mask, delta);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
				std::cout<<"Recieved input for "<<player.first<<std::endl;
				for(auto i:mask)std::cout<<i;
				std::cout<<std::endl;
				}
			}
		}
		/**
		 * @brief Get the mask object of the specified id.
		 *
		 * @param id ID of the requested player
		 * @return input_type returns a mask of input
		 */
		input_type get_mask(ID id) {
			return resource_store->input.get_mask(id);
		}
		void bot_inp_reg() {
			input_type inp;
			inp.push_back(1);
			inp.push_back(0);
			inp.push_back(0);
			inp.push_back(0);
			for(auto &player_i:players_map) {
				if(player_i.first<0)
					resource_store->input.register_input(input_return_type(player_i.first, inp));
			}
		}
		public:
		input_return_type get_input() {
			input_return_type input;
			input.first = main_player_id;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				input.second.push_back(1);
			}
			else input.second.push_back(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				input.second.push_back(1);
			}
			else
				input.second.push_back(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				input.second.push_back(1);
			}
			else
				input.second.push_back(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				input.second.push_back(1);
			}
			else
				input.second.push_back(0);

			return input;
		}
		//

		private:
		Camera main_camera;
		public:
		void focus_on(ID id) {
			if(players_map.find(id) != players_map.end()) {
				main_camera.e_position.x = players_map.at(id).getPosition().x * 1024;
				main_camera.e_position.z = players_map.at(id).getPosition().z - 2000;
			}
		}
		private:
		void draw_all_players() {
			for(auto &player_i:players_map) {
				draw_player(player_i.second);
			}
		}
		void draw_player(PlayerCar& player) {
			int index = map.get_grid_index(player.getPosition().z);
			Line &temp_line = map.lines[index];
			player.drawSprite(map.lines[index]);
		}
		private:
		const PlayerCar& getPlayer(ID id) {
			return players_map.at(id);
		}


		Collision collision;


	};
}
#endif // GAME_SIMULATOR_HPP