#ifndef NETWORKING_HPP
#define NETWORKING_HPP

#include <SFML/Network.hpp>
<<<<<<< HEAD
=======
#include <SFML/Graphics.hpp>
>>>>>>> 14c9370e46fcea7a2e44652a711bfecafecbb722
#include <thread>
#include <iostream>

#include <unistd.h>
namespace cp{
	class NetworkManager{

		public:

<<<<<<< HEAD
		// sf::TcpSocket server;
		// sf::TcpSocket client;
		sf::Socket::Status s_status;
		sf::Socket::Status c_status;
		std::thread n_thread;
		static sf::TcpSocket socket;
=======
		sf::Socket::Status s_status;
		sf::Socket::Status c_status;
		std::thread n_thread;
		static sf::TcpSocket client;
>>>>>>> 14c9370e46fcea7a2e44652a711bfecafecbb722
		NetworkManager();
		// ~NetworkManager();

		static void createServer();
		static void createClient();

		static void run(int type);
<<<<<<< HEAD
		static void receiveData(sf::Vector3f &pos);
		static void receive(sf::Vector3f &pos);
=======
		static void sendData(sf::Vector3f pos);
		static void send(sf::Vector3f pos);
>>>>>>> 14c9370e46fcea7a2e44652a711bfecafecbb722
	};
}
#endif //NETWORKING_HPP