/**
 * @file ServerState.hpp
 * @author Vijay
 * @brief The ServerState maintains and simulate online game play
 * @version 0.1
 * @date 2019-02-28
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef SERVER_STATE_HPP
#define SERVER_STATE_HPP

#include "States/State.hpp"
#include "Game.hpp"
#include "States/GameSimulator.hpp"
#include "Network/Client.hpp"
#include <map>
#include <vector>
#include <fstream>
#include <set>

namespace cp{
	/**
	 * @brief   ServerState is the state where network updates
	 * 			takes place. It is the game simulator which simulates the game and then
	 * 			update the relevant data over the network.
	 *
	 */
	class ServerState : public State {
		private:
		using TcpClient_ptr = std::shared_ptr<Client>;
		public:
		ServerState(GameDataRef _data, std::set<TcpClient_ptr> clients);
		~ServerState();

		virtual void handle_input(float delta);
		virtual void update(float delta);
		virtual void draw(float delta);
		virtual void pause() {}
		virtual void resume() {}
		virtual void init();

		private:
		GameSimulator simulator;
		GameDataRef game_data;

		std::vector<Client::key_input_type> inputs;
		std::set<TcpClient_ptr> clients;
		GameSimulatorSnap temp_snap;

		void collect_network_inputs();
		void use_collected_inputs();

		void generate_outputs();
		void use_generated_outputs();
		void simulate_server_room();

		// Log stuffs
		private:
		std::ofstream fout;
	};
}

#endif // SERVER_STATE_HPP