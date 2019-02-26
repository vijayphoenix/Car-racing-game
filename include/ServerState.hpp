#ifndef SERVER_STATE_HPP
#define SERVER_STATE_HPP

#include "State.hpp"
#include "vector"
#include "Game.hpp"
#include "GameSimulator.hpp"
#include "map"
#include "Client.hpp"
#include "fstream"

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
		virtual void update(float delta);
		virtual void draw(float delta);
		virtual void pause(){}
		virtual void resume(){}
		virtual void init();

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

		// Log stuffs
		private:
		std::ofstream fout;
	};
}

#endif // SERVER_STATE_HPP