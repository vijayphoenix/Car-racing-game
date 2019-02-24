#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Line.hpp"
#include <SFML/Graphics.hpp>
#include "Car.hpp"
#include <thread>

namespace cp {
	class Camera {
		sf::Vector3f 	e_speed;
		float       	camD    		= 0.84; //camera depth
		public:
		std::thread::id id;
		sf::Vector3f 	e_position 		= sf::Vector3f(0, 1500, 0);
		const sf::Vector3f& getPosition() const {
			return e_position;
		}
		const sf::Vector3f& getSpeed() const {
			return e_speed;
		}
		void catch_player(const Car& player) {
			e_speed = player.getSpeed();
		}
		float getCamD() const {
			return camD;
		}

		void handle_input() {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
				e_position.z += 200;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				e_position.z -= 200;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				e_position.x -=100;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
				e_position.x +=100;
			}
		}

	};
}
#endif //CAMERA_HPP