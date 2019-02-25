#include "ClientState.hpp"

namespace cp {
	ClientState::ClientState(GameDataRef _data)
		 : game_data(_data), simulator(_data){
	}

	void ClientState::collect_inputs() {
		input_to_send = simulator.get_input();
	}

	void ClientState::use_collected_inputs() {
		server.send_inputs(input_to_send);
	}

	void ClientState::get_network_snap() {
		snap = server.get_network_snap();
	}

	void ClientState::use_network_snap() {
		simulator.use_snap(snap, true);
	}
}