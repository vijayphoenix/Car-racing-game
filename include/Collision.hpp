#ifndef COLLISION_HPP
#define COLLISION_HPP

#include<SFML/Graphics.hpp>

namespace cp{
	class Collision{
		public:
		Collision				(){}
		~Collision				(){}

		bool detect_collision	(sf::Sprite s1,sf::Sprite s2){
			return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
		}

		private:
	};
}
#endif //COLLISION_HPP