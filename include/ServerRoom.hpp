/**
 * @file ServerRoom.hpp
 * @author Anjani (cs17btech11002@iith.ac.in)
 * @brief Simple Server room displayed before Online Play Starts
 * @version 0.1
 * @date 2019-02-27
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SERVER_ROOM_HPP
#define SERVER_ROOM_HPP

#include "State.hpp"
#include "Game.hpp"
#include "Client.hpp"
#include <iostream>
#include <cstring>
#include "ServerState.hpp"


namespace cp {
	class ServerRoom :public State{
		private:
		sf::Sprite background_sprite;
		GameDataRef game_data;
		std::vector<Client*> clients_res;
	  	public:
		ServerRoom(GameDataRef _data)
			: game_data(_data) {
		}
		~ServerRoom() {
		}

		void init() {
			std::cout << "Server Creating" << std::endl;
			sf::TcpListener listener;
			// bind the listener to a port
			std::cout << "Opening Port" << std::endl;
			if (listener.listen(53000) != sf::Socket::Done)
			{
				std::cerr << "Error Listening Port" << std::endl;
			}
			else
				std::cout << "Port Opened" << std::endl;

			// accept a new connection
			std::cout << "Listening for Client" << std::endl;
			clients_res.push_back(new Client(12312));
			if (listener.accept(clients_res[0]->get_socket()) != sf::Socket::Done) {
				std::cerr << "Error accepting client" << std::endl;
			}
			else {
				std::cout << "connected" << std::endl;
				char data[100] = "VijayChutiyaHai";
				// TCP socket:
				if (clients_res[0]->get_socket().send(data, strlen(data)) != sf::Socket::Done) {
					std::cerr << "Data transfer not successful" << std::endl;
				}
				else {
					std::cout << "Sent a fact" << std::endl;
				}
			}
		}
		virtual void handle_input(float delta) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				game_data->machine.remove_state();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
				game_data->machine.add_state(StateRef(new ServerState(game_data, clients_res)), true);
			}
		}
		virtual void update(float delta) {
			// std::cout<<"Press V to continue"<<std::endl;
		}
		virtual void draw(float delta) {

		}
		virtual void pause() {}
		virtual void resume() {}
	};
}
#endif // SERVER_ROOM_HPP