#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include<SFML/Graphics.hpp>

namespace cp
{

	class InputManager
	{
	private:
	public:
		// InputManager();
		// ~InputManager();

		bool is_sprite_clicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window);

		sf::Vector2i get_mouse_position(sf::RenderWindow &window);
	};

} // namespace cp

#endif