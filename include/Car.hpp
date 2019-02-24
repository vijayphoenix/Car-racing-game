#ifndef CAR_HPP
#define CAR_HPP

#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "Line.hpp"
#include <vector>

// Drawable has a sprite and it's associated scaling and position.
// Assuming it inherits from drawable and also from entity
// Entity class have a location in 3D world, speed, acceleration and info's such as width, height, length.
namespace cp{
	class Car{
		public:
		Car						(GameDataRef _data, int car_num);
		~Car					();

		void 		 draw_car	();
		virtual void update_car	(float dt, const std::vector<Line> &lines, float segL)= 0;
		sf::Vector3f getPosition() const {
			return e_position;
		}
		sf::Vector3f getSpeed() const {
			return e_speed;
		}
		// protected:
		///////// Sprite Info's //////////////////////////////////
		int car_image_num;
		sf::Sprite sprite;
		//////////////////////////////////////////////////////////

		////////// Reference to game data and resources //////////
		GameDataRef data;
		//////////////////////////////////////////////////////////

		////////// Entity info's /////////////////////////////////
		sf::Vector3f e_position;
		sf::Vector3f e_speed;
		sf::Vector3f e_acceleration;
		sf::Vector3f e_decleration;
		sf::Vector3f e_max_speed;
		float centrifugal = 0.5;
		//////////////////////////////////////////////////////////
	};
}
#endif //CAR_HPP
