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
	enum class SnapFlag {
		NETWORK_SNAP, OFFLINE_SNAP
	};
	class GameSimulatorSnap {
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


		input_type get_mask(int i);
		// Stuffs for getting logs
		std::ofstream fout;



		// Game Stuff
		public:
		void init();
		void handle_input(float delta);
		void draw(float delta);
		void update(float delta);

		private:
		void drawSprite(Line &line);
		// All the game Entities
		using CarRef = std::shared_ptr<PlayerCar>;
		using BotRef = std::shared_ptr<Bot>;
		GameMap map;
		Camera main_camera;
		BotRef bot[TOTAL_BOTS];
		std::vector<ID> bot_id;
		Collision collision;
	};
}
#endif // GAME_SIMULATOR_HPP