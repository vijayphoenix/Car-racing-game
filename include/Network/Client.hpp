/**
 * @file Client.hpp
 * @author Vijay
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
#include "States/GameSimulator.hpp"
#include "SFML/Network.hpp"

namespace cp {
	class Client {
		public:
		using ID = long long int;
		using IP = std::string;
		using key_input_type = std::pair<ID, std::vector<bool>>;
		private:
		/**
		 * @brief id of the current client
		 *
		 */
		ID id;
		/**
		 * @brief Internal Socket object of the Client.
		 *
		 */
		sf::TcpSocket socket;
		/**
		 * @brief Contains the last status of any recieve and send call
		 *
		 */
		sf::Socket::Status last_status;

		public:
		/**
		 * @brief Construct a new Client object
		 *
		 * @param identity desired id of the client.
		 */
		Client(ID identity):id(identity){
		}
		/**
		 * @brief Get the socket object
		 *
		 * @return sf::TcpSocket& Internal Socket of the client.
		 */
		sf::TcpSocket &get_socket() {
			return socket;
		}
		/**
		 * @brief Get the identity of the Client.
		 *
		 * @return ID id of the client.
		 */
		ID get_identity() const {
			return id;
		}

		/**
		 * @brief Friend function for operator<< overloaded for sending snap over the network.
		 *
		 * @param client Client that you want to send the snap to.
		 * @param snap The snap that you want to send.
		 * @return Client& Returns Client object back.
		 */
		friend Client &operator<<(Client &client, const GameSimulatorSnap &snap) {
			sf::Packet packet;
			packet<<snap;
			client.send_packet(packet);
			return client;
		}
		/**
		 * @brief Overloaded operator>> to send labelled input over the network.
		 *
		 * @param client The client object to which you want to send the labelled input
		 * @param labelled_input The labelled input that you want to send.
		 * @return Client& Returns back the Client Reference.
		 */
		friend Client& operator>>(Client& client, key_input_type& labelled_input) {
			sf::Uint64 size;
			bool res;
			sf::Packet packet;
			client.recieve_packet(packet);
			if(client.getLastStatus() == sf::Socket::Done) {
				packet>>labelled_input.first>>size;
				for(int i=0; i<size; i++) {
					packet>>res;
					labelled_input.second.push_back(res);
				}
			}
			return client;
		}
		/**
		 * @brief Utility function to connec to host.
		 *
		 * @param ip IP of the host.
		 * @param port PORT number of the host.
		 */
		void connect_to(const std::string & ip, int port) {
			// sf::seconds rem = 10;
			while((last_status = socket.connect(ip, port, sf::seconds(5))) == sf::Socket::Partial) {
				std::cout<<"Trying to connect to ip"<<std::endl;
			}
		}
		/**
		 * @brief Utility to send packet over the network to the client connected to other end.
		 *
		 * @param packet The packet that you want to send .
		 */
		void send_packet(sf::Packet& packet) {
			while ((last_status = socket.send(packet)) == sf::Socket::Partial) {
				std::cout << "Partially sent" << std::endl;
			}
		}
		/**
		 * @brief Utility function to recieve a packet from other end.
		 *
		 * @param packet The packet that you want to recieve data into.
		 */
		void recieve_packet(sf::Packet& packet) {
			while((last_status=socket.receive(packet)) == sf::Socket::Partial) {
				std::cout<<"Partially recieved"<<std::endl;
			}
		}
		/**
		 * @brief Get the Last Status object
		 *
		 * @return sf::Socket::Status Returns the status of the last call to send/recieve.
		 */
		sf::Socket::Status getLastStatus() const {
			return last_status;
		}
	};
}
#endif //CLIENT_HPP