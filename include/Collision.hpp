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
		bool handle_collision	(Car& car1, Car& car2, GameMap& map, float cor) {
			int index = map.get_grid_index(car2.e_position.z);
			int diff = index % map.getGridCount() - map.get_grid_index(car1.e_position.z) % map.getGridCount();

			if (std::abs(diff) <= 4)
			{
				bool coll = detect_collision(car1.sprite, car2.sprite);
				sf::Vector3f tmp1 = car1.e_speed;
				sf::Vector3f tmp2 = car2.e_speed;
				if (diff > 0 and coll)
				{
					car1.e_speed.z = cor!=0?(((1-cor)/2)*tmp1.z + ((1+cor)/2)*tmp2.z):0;
					car2.e_speed.z = cor!=0?(((1-cor)/2)*tmp2.z + ((1+cor)/2)*tmp1.z):tmp2.z;
					car1.onCollision(car2, 1, cor);
					car2.onCollision(car1, 0, cor);
				}
				else if (diff <= 0 and coll)
				{
					car1.e_speed.z = cor!=0?(((1-cor)/2)*tmp1.z + ((1+cor)/2)*tmp2.z):0;
					car2.e_speed.z = cor!=0?(((1-cor)/2)*tmp2.z + ((1+cor)/2)*tmp1.z):tmp2.z;
					car1.onCollision(car2, 0, cor);
					car2.onCollision(car1, 1, cor);
				}
				return coll;
			}
		}

		private:
	};
}
#endif //COLLISION_HPP