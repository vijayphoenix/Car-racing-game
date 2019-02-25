/**
 * @file Client.hpp
 * @author Anjani Kumar (cs17btech11002@iith.ac.in)
 * @brief Client class refers to a another pc connected over network
 * @version 0.1
 * @date 2019-02-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include "GameSimulator.hpp"

namespace cp {
	class Client {
		public:
		using ID = long long int;
		using IP = std::string;
		using PORT = uint32_t;
		using key_input_type = std::pair<ID, std::vector<bool>>;
		private:
		ID id;
		IP ip;
		PORT port;

		public:
		ID get_identity() const ;
		key_input_type get_inputs() const ;
		void send_snap(const GameSimulatorSnap& snap) const ;
	};
}
#endif //CLIENT_HPP