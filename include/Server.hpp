/**
 *
 * @file Server.hpp
 * @author Anjani Kumar (cs17btech11002@iith.ac.in)
 * @brief Server class that handles the data sending over the network
 * @version 0.1
 * @date 2019-02-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "GameSimulator.hpp"

namespace cp {
	class Server {
		private:
		long long int ID;
		std::string IP;
		public:
		void send_inputs(GameSimulator::input_return_type inputs);
		GameSimulatorSnap get_network_snap();
	};
}

#endif //SERVER_HPP