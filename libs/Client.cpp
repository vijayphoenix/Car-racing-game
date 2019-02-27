#include "Client.hpp"

namespace cp {
	void Client::send_snap(const GameSimulatorSnap& snap) const {
		// std::cout<<"Sending Snap";
	}
	Client::key_input_type Client::get_inputs() const {
		std::vector<bool> mask;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))mask.push_back(1);
		else mask.push_back(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))mask.push_back(1);
		else mask.push_back(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))mask.push_back(1);
		else mask.push_back(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))mask.push_back(1);
		else mask.push_back(0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			std::cout<<"Sent the following mask"<<std::endl;
			for(auto i:mask)std::cout<<i;
			std::cout<<std::endl;
		}
		return Client::key_input_type(12312, mask);
	}

	sf::TcpSocket & Client::get_socket() {
		return socket;
	}
	Client::ID Client::get_identity() const {
		return id;
	}
}