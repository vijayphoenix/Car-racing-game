#include "InputManager.hpp"

namespace cp{
	bool InputManager::is_sprite_clicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window){
		if(sf::Mouse::isButtonPressed(button)){
			sf::IntRect temp(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
			if(temp.contains(sf::Mouse::getPosition(window)))
				return true;
		}
		return false;
	}

	sf::Vector2i InputManager::get_mouse_position(sf::RenderWindow &window){
		return sf::Mouse::getPosition(window);
	}
}