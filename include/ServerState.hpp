#ifndef SERVER_STATE_HPP
#define SERVER_STATE_HPP

#include "State.hpp"
#include "vector"
#include "Game.hpp"
#include "GameSimulator.hpp"
#include "map"
#include "Client.hpp"

namespace cp{
	/**
	 * @brief   ServerState is the state where network updates
	 * 			takes place. It is the game simulator which simulates the game and then
	 * 			update the relevant data over the network.
	 *
	 */
	class ServerState : public State {
		public:
		ServerState(GameDataRef _data);
		~ServerState();

		virtual void handle_input(float delta);
		virtual void update();
		virtual void draw();
		virtual void pause();
		virtual void resume();

		private:
		GameSimulator simulator;
		GameDataRef game_data;

		std::vector<Client::key_input_type> inputs;
		std::vector<Client> clients;
		GameSimulatorSnap temp_snap;

		void collect_network_inputs();
		void use_collected_inputs();

		void generate_outputs();
		void use_generated_outputs();

	};
}

#endif // SERVER_STATE_HPP