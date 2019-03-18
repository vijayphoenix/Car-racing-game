/**
 * @file ClientRoom.hpp
 * @author Vijay
 * @brief The client room that is displayed on client's computer just before online game play
 * @version 0.1
 * @date 2019-02-28
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef CLIENT_ROOM_HPP
#define CLIENT_ROOM_HPP

#include "States/State.hpp"
#include "Game.hpp"
#include "Network/Server.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>
#include "States/ClientState.hpp"

namespace cp{
	class ClientRoom : public State{
		private:
		using Server_ptr = std::shared_ptr<Server>;
		/**
		 * @brief Pointer to the game_data.
		 *
		 */
		std::string HOST_IP;
		GameDataRef game_data;
		/**
		 * @brief Pointer pointer the server on the other side of the network.
		 *
		 */
		Server_ptr server_ptr;
		/**
		 * @brief Unique id assigned to this computer by the server.
		 *
		 */
		int unique_id;
		/**
		 * @brief Status of the looby (GameStarted/ServerClosed/ServerWaiting).
		 *
		 */
		int HAS_TO_WAIT;


		bool update_required = true;

		std::ofstream fout;
		public:
		ClientRoom(GameDataRef _data)
			: game_data(_data), fout("ClientRoom"){}
		~ClientRoom(){}

		/**
		 * @brief Initializing the ClientRoom components.
		 *
		 */
		void init() {
			std::cout<<"Connecting to game host"<<std::endl;
			server_ptr = Server_ptr(new Server());
			// Take input IP
			enterIP();
			server_ptr->connect_to("HOST_IP", PORT);
			sf::Socket::Status status = server_ptr->getLastStatus();
			if (status != sf::Socket::Done) {
				std::cout << "error connecting to server" << std::endl;
				game_data->machine.remove_state();
				update_required = false;
			}
			else {
				std::cout << " Connected " << std::endl;
				sf::Packet packet;
				(*server_ptr).get_socket().receive(packet);
				packet>>unique_id;
				std::cout<<"Connected to "<<unique_id<<std::endl;
			}
		}

		/**
		 * @brief THis function provides the interface to handle_input in ClientRoom.
		 *
		 * @param delta TIme difference between two handle_input calls.
		 */
		void handle_input(float delta) {
			if(!update_required)return;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				std::cout<<"User exited the lobby"<<std::endl;
				game_data->machine.remove_state();
				update_required = false;
			}
		}

		void enterIP(){
			sf::RenderWindow ipadd(sf::VideoMode(500,150) , "Enter IP Address");
			sf::Text text1 , text2;
			sf::Font font;
			font.loadFromFile("../res/SFAtarianSystem.ttf");
			text1.setFont(font);
			text1.setString("ENTER HOST IP ADDRESS");
			text1.setPosition(75 ,40);
			text1.setCharacterSize(24);
			text1.setStyle(sf::Text::Bold);
			text1.setOutlineThickness(2);
			text2.setFont(font);
			text2.setPosition(75 ,80);
			text2.setCharacterSize(24);
			text2.setStyle(sf::Text::Bold);
			text2.setOutlineThickness(2);
			while(ipadd.isOpen()){
				ipadd.clear();
				ipadd.draw(text1);
				ipadd.draw(text2);
				sf::Event event;
				while(ipadd.pollEvent(event)){
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
						HOST_IP = text2.getString();
						ipadd.close();
					}
					switch (event.type)
					{
						case sf::Event::Closed:
							ipadd.close();
							break;
						case sf::Event::TextEntered:
							text2.setString(text2.getString()+event.text.unicode);
							break;
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
						text2.setString(text2.getString().substring(0,text2.getString().getSize()-1));
						continue;
					}
				}
				ipadd.display();
			}
		}
		/**
		 * @brief Provides an interface to update the ClientRoom
		 *
		 * @param delta TIme difference between two update calls
		 */
		void update(float delta){
			get_notifications();
			use_notification();
		}

		/**
		 * @brief Draw the components on the screen.
		 *
		 * @param delta
		 */
		void draw(float delta) {
		}

		/**
		 * @brief Get the notifications from the server.
		 *
		 */
		void get_notifications() {
			sf::Packet packet;
			server_ptr->recieve_packet(packet);
			if(server_ptr->getLastStatus() != sf::Socket::Done) {
				HAS_TO_WAIT = 2;
				std::cout<<"Something is partial"<<std::endl;
			}
			else
				packet>>HAS_TO_WAIT;
			std::cout<<"The packet says to "<<HAS_TO_WAIT<<std::endl;
		}
		/**
		 * @brief Utility function to use_recieved notification.
		 *
		 */
		void use_notification() {
			if(HAS_TO_WAIT == 1)return;
			if(HAS_TO_WAIT == 0) {
				game_data->machine.add_state(StateRef(new ClientState(game_data, server_ptr, unique_id)));
				update_required = false;
			}
			else if(HAS_TO_WAIT == 2) {
				game_data->machine.remove_state();
				update_required = false;
			}
		}
	};
}
#endif //CLIENT_ROOM_HPP