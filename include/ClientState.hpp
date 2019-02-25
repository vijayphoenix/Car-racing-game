/**
 * @file ClientState.hpp
 * @author Anjani Kumar (cs17btech11002@iith.ac.in)
 * @brief Handles communication between the computer and the server.
 * @version 0.1
 * @date 2019-02-26
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef CLIENT_STATE_HPP
#define CLIENT_STATE_HPP

#include "State.hpp"
#include "Game.hpp"
#include "GameSimulator.hpp"
#include "Server.hpp"

namespace cp {
	class ClientState :public State {
		private:
		GameDataRef game_data;
		GameSimulator simulator;
		GameSimulator::input_return_type input_to_send;
		Server server;
		GameSimulatorSnap snap;

		void collect_inputs();
		void use_collected_inputs();

		void get_network_snap();
		void use_network_snap();
		public:
		ClientState(GameDataRef _data);
		~ClientState();

	};
}
#endif //CLIENT_STATE_HPP