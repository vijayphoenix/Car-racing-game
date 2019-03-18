#include "ResourceManagers/InputManager.hpp"
#include "Objects/Bot.hpp"

namespace cp{
	InputManager::InputManager(){
	}
	InputManager::~InputManager(){
	}
	bool InputManager::is_sprite_clicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow &window) {
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
	void InputManager::register_input(register_input_type input_pair) {
		mp[input_pair.first] = input_pair.second;
	}
	InputManager::input_type InputManager::get_mask(ID id) {
		return mp[id];
	}
}
