#include "NetworkManager.hpp"
#include <cstring>

<<<<<<< HEAD
sf::TcpSocket cp::NetworkManager::socket;
namespace cp{
	NetworkManager::NetworkManager() {
	}
	void NetworkManager::createServer() {
		// sleep(5);
		std::cout<<"Server Creating"<<std::endl;
		run(1);
	}
	void NetworkManager::createClient() {
		std::cout<<"ClientCreating"<<std::endl;
		run(0);
	}
	void NetworkManager::run(int type) {
		if(type == 1) {
			sf::TcpListener listener;
			// bind the listener to a port
			std::cout<<"Opening Port"<<std::endl;
			if (listener.listen(53000) != sf::Socket::Done)
			{
				std::cerr<<"Error Listening Port"<<std::endl;
			}
			else std::cout<<"Port Opened"<<std::endl;

			// accept a new connection
			sf::TcpSocket client;
			std::cout<<"Listening for Client"<<std::endl;
			if (listener.accept(client) != sf::Socket::Done)
			{
				std::cerr<<"Error accepting client"<<std::endl;
			}
			else std::cout<<"connected"<<std::endl;

			char data[100] = "VijayChutiyaHai";
			// TCP socket:
			if (client.send(data, strlen(data)) != sf::Socket::Done)
			{
				std::cerr<<"Data transfer not successful"<<std::endl;
			}
			else std::cout<<"Sent a fact"<<std::endl;
		}
		else {
			sf::Socket::Status status = socket.connect("10.42.0.1", 53000);
			if (status != sf::Socket::Done)
			{
				std::cerr<<"error connecting to server"<<std::endl;
			}
			else {
				std::cout<<"connected "<<std::endl;
				char data[100];
				std::size_t received;
				if (socket.receive(data, 100, received) != sf::Socket::Done)
				{
					std::cerr << "error data not received from server" << std::endl;
				}
				for(int i = 0; i < received; i++)
				{
					std::cout<<data[i];
				}
				std::cout << std::endl;
				std::cout << "Received " << received << " bytes" << std::endl;

			}
		}
	}
	void NetworkManager::receiveData(sf::Vector3f &pos){
		std::thread receiverThread(receive, std::ref(pos));
		receiverThread.join();
	}
	void NetworkManager::receive(sf::Vector3f &pos) {
		sf::Packet packet;
		if (socket.receive(packet) != sf::Socket::Done) {
			std::cerr << "error not able to receive data" << std::endl;
		}
		else {
			packet>>pos.x>>pos.y>>pos.z;
=======
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
		// std::cout<<"Sending the packets"<<std::endl;
		if (client.send(packet) != sf::Socket::Done) {
			std::cout << "Data transfer not successful" << std::endl;
		}
		else {
			std::cout << "Sent a packet " << std::endl;
>>>>>>> 14c9370e46fcea7a2e44652a711bfecafecbb722
		}
	}
}