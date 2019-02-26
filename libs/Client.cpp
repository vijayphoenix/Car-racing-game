#include "Client.hpp"

namespace cp {
	void Client::send_snap(const GameSimulatorSnap& snap) const {
		std::cout<<"Sending Snap";
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

		return Client::key_input_type(0, mask);
	}
}