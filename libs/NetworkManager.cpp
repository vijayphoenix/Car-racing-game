#include "NetworkManager.hpp"
#include <cstring>

sf::TcpSocket cp::NetworkManager::client;

namespace cp{

	NetworkManager::NetworkManager() {
	}
	void NetworkManager::createServer() {
		std::cout<<"Server Creating"<<std::endl;
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
		if (listener.accept(NetworkManager::client) != sf::Socket::Done)
		{
			std::cerr << "Error accepting client" << std::endl;
		}
		else {
			std::cout << "connected" << std::endl;
			char data[100] = "VijayChutiyaHai";
			// TCP socket:
			if (client.send(data, strlen(data)) != sf::Socket::Done) {
				std::cerr << "Data transfer not successful" << std::endl;
			}
			else {
				std::cout << "Sent a fact" << std::endl;
			}
		}
	}
	void NetworkManager::createClient() {
		std::cout<<"ClientCreating"<<std::endl;
		run(0);
	}
	void NetworkManager::run(int type) {
	}
	void NetworkManager::sendData(sf::Vector3f pos) {
		std::thread senderThread(send, pos);
		senderThread.join();
	}
	void NetworkManager::send(sf::Vector3f pos) {
		sf::Packet packet;
		packet<<pos.x<<pos.y<<pos.z;
		if (client.send(packet) != sf::Socket::Done) {
			std::cerr << "Data transfer not successful" << std::endl;
		}
		else {
		}
	}
}