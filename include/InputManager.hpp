#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>

namespace cp
{
	class InputManager {
		private:
		using ID = long long int;
		using input_type = std::vector<bool>;
		using register_input_type = std::pair<ID, input_type>;
		std::map<ID, input_type> mp;
		public : InputManager();
		~InputManager();
		bool is_sprite_clicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window);
		sf::Vector2i get_mouse_position(sf::RenderWindow &window);
		void register_input(register_input_type input_pair);
		input_type get_mask(ID id);
	};
} // namespace cp

#endif