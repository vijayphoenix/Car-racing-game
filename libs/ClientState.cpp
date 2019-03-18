#include "States/ClientState.hpp"

namespace cp {
	ClientState::ClientState(GameDataRef _data, Server_ptr server, int unique_id)
		: game_data(_data), simulator(_data), fout("ClientState.log"),server(server), my_id(unique_id) {
		fout << "Executing ClientState" << std::endl;
		fout<<"Unique id for this client is:"<<unique_id<<std::endl;
		fout << "Returning from ClientState" << std::endl;
	}

	void ClientState::collect_inputs() {
		input_to_send = simulator.get_input();
	}

	void ClientState::use_collected_inputs() {
		(*server)<<input_to_send;
	}

	void ClientState::get_network_snap() {
		(*server)>>snap;
	}

	void ClientState::use_network_snap() {
		simulator.use_snap(snap, true);
	}

	void ClientState::init() {
		fout << "Executing init" << std::endl;
		fout << "Connecting all the clients" << std::endl;
		simulator.init();
		std::cout<<"Got id:"<<my_id<<std::endl;
		simulator.add_external_player(my_id);
		simulator.update_main_player(my_id);
		fout << "Returning from init" << std::endl;
	}

	void ClientState::handle_input(float delta) {
		sf::Event event;
		while (game_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				game_data->machine.add_state(StateRef(new GameOverState(game_data)), true);
			}
		}
		if (server->getLastStatus() == sf::Socket::Disconnected) {
			game_data->machine.remove_state();
			return;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			game_data->machine.remove_state();
			return;
		}
		std::cout<<"Collecting outputs"<<std::endl;
		collect_inputs();
		use_collected_inputs();
		std::cout<<"Inputs collected"<<std::endl;
		std::cout<<"Last status:"<<server->getLastStatus()<<std::endl;
	}

	void ClientState::draw(float delta) {
		simulator.draw(delta);
	}

	void ClientState::update(float delta) {
		std::cout<<"Getting Snap"<<std::endl;
		get_network_snap();
		use_network_snap();
		std::cout<<"Snap Recieved"<<std::endl;
		simulator.update(delta);
		std::cout<<"Updated Simulator"<<std::endl;
	}
}