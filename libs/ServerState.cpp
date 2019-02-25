#include "ServerState.hpp"

namespace cp {
	ServerState::ServerState(GameDataRef _data)
		:game_data(_data), simulator(_data) {

	}

	void ServerState::collect_network_inputs() {
		for(auto &client:clients) {
			inputs.push_back(client.get_inputs());
		}
	}

	void ServerState::use_collected_inputs() {
		for(auto &input:inputs) {
			game_data->input.register_input(input);
		}
	}

	void ServerState::handle_input(float delta) {
		collect_network_inputs();
		use_collected_inputs();
		simulator.handle_input(delta);
	}

	void ServerState::generate_outputs() {
		temp_snap = simulator.get_current_snap(SnapFlag::NETWORK_SNAP);
	}

	void ServerState::use_generated_outputs() {
		for(auto &client:clients) {
			client.send_snap(temp_snap);
		}
	}
}