#ifndef COLLISION_HPP
#define COLLISION_HPP

#include<SFML/Graphics.hpp>
#include<Car.hpp>
#include<GameMap.hpp>
namespace cp{
	class Collision{
		public:
		Collision				(){}
		~Collision				(){}

		bool detect_collision	(const sf::Sprite &s1,const sf::Sprite &s2){
			return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
		}
		void handle_collision	(Car& car1, Car& car2, GameMap& map) {
			int index = map.get_grid_index(car2.e_position.z);
			int diff = index % map.getGridCount() - map.get_grid_index(car1.e_position.z) % map.getGridCount();

			if (std::abs(diff) <= 4)
			{
				bool coll = detect_collision(car1.sprite, car2.sprite);
				if (diff > 0 and coll)
				{
					car1.onCollision(car2, 1);
					car2.onCollision(car1, 0);
				}
				else if (diff <= 0 and coll)
				{
					car1.onCollision(car2, 0);
					car2.onCollision(car1, 1);
				}
			}
		}

		private:
	};
}
#endif //COLLISION_HPP