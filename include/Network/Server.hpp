/**
 *
 * @file Server.hpp
 * @author Vijay
 * @brief Server class that handles the data sending over the network
 * @version 0.1
 * @date 2019-02-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "States/GameSimulator.hpp"

namespace cp {
	class Server {
		private:
		using ID = long long int;\
		using key_input_type = std::pair<ID, std::vector<bool>>;
		long long int id;
		sf::TcpSocket socket;
		sf::Socket::Status last_status;

	  	public:
		/**
		 * @brief Construct a new Server object
		 *
		 */
		Server() {
		}
		/**
		 * @brief Get the identity object
		 *
		 * @return ID id of the Server.
		 */
		ID get_identity() const {
			return id;
		}
		/**
		 * @brief Get the socket object
		 *
		 * @return sf::TcpSocket& INternal handle of the socket.
		 */
		sf::TcpSocket& get_socket() {
			return socket;
		}
		/**
		 * @brief Overloaded operator<< to send the labelled input.
		 *
		 * @param server The server that you want to send the labelled input to.
		 * @param labelled_input The labelled input to send.
		 * @return Server& Returns back the server reference.
		 */
		friend Server& operator<<(Server& server, const key_input_type& labelled_input) {
			sf::Packet packet;
			//
			sf::Uint64 size = labelled_input.second.size();
			packet << labelled_input.first<<size;
			for (int i = 0; i < size; i++) {
				packet << labelled_input.second[i];
			}
			//
			server.send_packet(packet);
			return server;
		}
		/**
		 * @brief Overloaded operator>> to recieve GameSnaps.
		 *
		 * @param server The server that you want to recieve snap from.
		 * @param snap The snap reference for getting incoming snap.
		 * @return Server& Returns back the server.
		 */
		friend Server& operator>>(Server&server, GameSimulatorSnap& snap) {
			sf::Packet packet;
			server.recieve_packet(packet);
			if(server.getLastStatus() == sf::Socket::Done)
				packet>>snap;
			return server;
		}
		/**
		 * @brief Get the Last Status object
		 *
		 * @return sf::Socket::Status Status of the last function call to recieve/send.
		 */
		sf::Socket::Status getLastStatus() const {
			return last_status;
		}
		/**
		 * @brief connect to the specified port and ip
		 *
		 * @param ip IP of the server.
		 * @param port PORT of the server.
		 */
		void connect_to(const std::string &ip, int port) {
			while ((last_status = socket.connect(ip, port, sf::seconds(5))) == sf::Socket::Partial) {
				std::cout << "Trying to connect to ip:"<<ip << std::endl;
			}
		}
		/**
		 * @brief send packet
		 *
		 * @param packet
		 */
		void send_packet(sf::Packet& packet) {
			while((last_status = socket.send(packet)) == sf::Socket::Partial) {
				std::cout<<"Partially send"<<std::endl;
			}
		}
		void recieve_packet(sf::Packet& packet) {
			while((last_status = socket.receive(packet)) == sf::Socket::Partial) {
				std::cout<<"Paritally recieved"<<std::endl;
			}
		}
	};
}

#endif //SERVER_HPP