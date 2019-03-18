#include "States/ServerState.hpp"
#include "Network/ServerRoom.hpp"

namespace cp {
	ServerState::ServerState(GameDataRef _data, std::set<TcpClient_ptr> clients)
		: game_data(_data), simulator(_data), fout("ServerState.log"), clients(std::move(clients)) {
		fout<<"Executing ServerState"<<std::endl;
		fout<<"Returning from ServerState"<<std::endl;
	}

	ServerState::~ServerState() {
		fout<<"Closed"<<std::endl;
		fout.close();
	}

	void ServerState::collect_network_inputs() {
		inputs.clear();
		for(auto &client:clients) {
			Client::key_input_type temp;
			(*client)>>temp;
			inputs.push_back(std::move(temp));
		}
	}

	void ServerState::use_collected_inputs() {
		for(auto &input:inputs) {
			game_data->input.register_input(input);
		}
	}

	void ServerState::handle_input(float delta) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			fout<<"Log register in handle_input"<<std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			std::cout << "Removing ServerState" << std::endl;
			game_data->machine.remove_state();
		}
		// std::cout<<"COllecting network inputs"<<std::endl;
		collect_network_inputs();
		// std::cout<<"Network input collected"<<std::endl;
		use_collected_inputs();
		game_data->input.register_input(simulator.get_input());
		simulator.handle_input(delta);
	}

	void ServerState::init() {
		fout<<"Executing init"<<std::endl;
		fout<<"Connecting all the clients"<<std::endl;
		simulator.init();
		for(auto &client:clients) {
			// std::cout<<"Have the player:"<<client->get_identity()<<std::endl;
			simulator.add_external_player(client->get_identity());
		}
		simulator.add_external_player(12312234);
		simulator.update_main_player(12312234);
		fout<<"Returning from init"<<std::endl;
	}

	void ServerState::draw(float delta) {
		simulator.draw(delta);
	}

	void ServerState::update(float delta) {
		// std::cout<<"Now updating simulator"<<std::endl;
		simulator.update(delta);
		// std::cout<<"Now generating snap";
		generate_outputs();
		// std::cout<<"Now sending snaps"<<std::endl;
		use_generated_outputs();
		// std::cout<<"Snaps sent"<<std::endl;
	}

	void ServerState::generate_outputs() {
		temp_snap = simulator.get_current_snap(SnapFlag::NETWORK_SNAP);
	}

	void ServerState::use_generated_outputs() {
		for(auto &client:clients) {
			(*client)<<temp_snap;
		}
	}
}