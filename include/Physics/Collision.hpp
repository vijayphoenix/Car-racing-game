#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>
#include <Objects/Car.hpp>
#include <Objects/GameMap.hpp>
#include <vector>
#include <mutex>
#include <future>

namespace cp{
	class Collision{
		private:
		static  std::mutex mutex_arr[MAX_ENTITIES];
		static  std::future<void> async_obj[MAX_ENTITIES];
	  	public:
		Collision() {}
		~Collision() {}

		/**
		 * @brief Parallel simulation for all the entities whether they are colliding or not.
		 *
		 * @param entities Vector of all the entities to simulate the physics on .
		 * @param map The map info to simulate external forces.
		 */
		static void simulate_physics(std::vector<Car *> &entities, GameMap &map) {
			size_t total_entites = entities.size();
			if (total_entites > MAX_ENTITIES)
				return;
			int i = 0;
			for (auto entity_ptr : entities) {
				async_obj[i] = std::async(single_entity_check, &entities, i, &map, Collision::mutex_arr);
				i++;
			}
			for (int i = 0; i < total_entites; i++) {
				async_obj[i].get();
			}
		}

		/**
		 * @brief Parallel execution for checking collision on a single entity with other entities.
		 *
		 * @param entites_ptr List of all the pointer to check collision with.
		 * @param index position of this entity in the vector list of all the entity.
		 * @param map_ptr A pointer to the map of the world.
		 * @param mutex_arr A mutex array to avoid concurrent access in critical section.
		 */
		static void single_entity_check(std::vector<Car *> *entites_ptr, int index, GameMap *map_ptr, std::mutex *mutex_arr) {
			std::vector<Car *> &entities = *entites_ptr;
			GameMap &map = *map_ptr;
			size_t total_entites = entities.size();
			for (int j = index + 1; j < total_entites; j++) {
				mutex_arr[index].lock();
				mutex_arr[j].lock();
				handle_collision(*entities[index], *entities[j], map);
				mutex_arr[j].unlock();
				mutex_arr[index].unlock();
			}
		}

		static void handle_collision(Car &car1, Car &car2, GameMap &map) {
			int index = map.get_grid_index(car2.e_position.z);
			int diff = index % map.getGridCount() - map.get_grid_index(car1.e_position.z) % map.getGridCount();

			if (std::abs(diff) <= 5)
			{
				bool coll = detect_collision(car1.sprite, car2.sprite);
				if(coll)cover_collided(car1, car2, diff, COEFFICIENT_OF_RESTITUTION);
			}
		}

		/**
		 * @brief Simulate the collision effect on two collidables.
		 *
		 * @param car1 The first colidable object.
		 * @param car2 The second collidable object.
		 * @param diff The difference in the grid position of the two given objets.
		 * @param cor COEFFICIENT of RESTITUTION.
		 */
		static void cover_collided(Car& car1, Car& car2, int diff, float cor) {
			sf::Vector3f tmp1 = car1.e_speed;
			sf::Vector3f tmp2 = car2.e_speed;

			car1.e_speed.z = cor != 0 ? (((1 - cor) / 2) * tmp1.z + ((1 + cor) / 2) * tmp2.z) : 0;
			car2.e_speed.z = cor != 0 ? (((1 - cor) / 2) * tmp2.z + ((1 + cor) / 2) * tmp1.z) : tmp2.z;

			if(diff>0) {

				car1.e_speed.z = cor != 0 ? (car1.e_speed.z > 50 ? car1.e_speed.z - 50 : 0) : car1.e_speed.z;

				car2.e_speed.z += cor != 0 ? 50 : 0;
				car1.e_speed.z = std::max(-100.0f, std::min(car1.e_speed.z, car1.e_max_speed.z));
				car2.e_speed.z = std::max(-100.0f, std::min(car2.e_speed.z, car2.e_max_speed.z));

				car1.onCollision();
				car2.onCollision();
			}
			else {
				car2.e_speed.z = cor != 0 ? (car2.e_speed.z > 50 ? car2.e_speed.z - 50 : 0) : car2.e_speed.z;

				car1.e_speed.z += cor != 0 ? 50 : 0;
				car2.e_speed.z = std::max(-100.0f, std::min(car2.e_speed.z, car2.e_max_speed.z));
				car1.e_speed.z = std::max(-100.0f, std::min(car1.e_speed.z, car1.e_max_speed.z));

				car2.onCollision();
				car1.onCollision();
			}
		}

		bool handle_collision(Car & car1, Car & car2, GameMap & map, float cor) {

			int index = map.get_grid_index(car2.e_position.z);
			int diff = index % map.getGridCount() - map.get_grid_index(car1.e_position.z) % map.getGridCount();

			if (std::abs(diff) <= 4)
			{
				bool coll = detect_collision(car1.sprite, car2.sprite);
				sf::Vector3f tmp1 = car1.e_speed;
				sf::Vector3f tmp2 = car2.e_speed;
				if (diff > 0 and coll)
				{
					car1.e_speed.z = cor != 0 ? (((1 - cor) / 2) * tmp1.z + ((1 + cor) / 2) * tmp2.z) : 0;
					car2.e_speed.z = cor != 0 ? (((1 - cor) / 2) * tmp2.z + ((1 + cor) / 2) * tmp1.z) : tmp2.z;
					car1.onCollision();
					car2.onCollision();
				}
				else if (diff <= 0 and coll)
				{
					car1.e_speed.z = cor != 0 ? (((1 - cor) / 2) * tmp1.z + ((1 + cor) / 2) * tmp2.z) : 0;
					car2.e_speed.z = cor != 0 ? (((1 - cor) / 2) * tmp2.z + ((1 + cor) / 2) * tmp1.z) : tmp2.z;
					car1.onCollision();
					car2.onCollision();
				}
				return coll;
			}
		}

		static bool detect_collision(const sf::Sprite &s1, const sf::Sprite &s2) {
			return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
		}

	  private:
	};
	inline std::mutex Collision::mutex_arr[MAX_ENTITIES] = {};
	inline std::future<void> Collision::async_obj[MAX_ENTITIES] = {};

}
#endif //COLLISION_HPP