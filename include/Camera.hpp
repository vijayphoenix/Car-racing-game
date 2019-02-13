#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Line.hpp"
#include <SFML/Graphics.hpp>

namespace cp {
	class Camera {
		public:
		float       camD    = 0.84; //camera depth
		float       speed 	= 0;	// The Camera speed
		int         H 		= 1500; // The Camera height
		sf::Vector3f position;
	};
}
#endif //CAMERA_HPP