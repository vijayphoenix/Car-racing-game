#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace cp
{
	class MainMenuState : public State {
	private:
	  GameDataRef 	data;
	  sf::Sprite 	background_sprite;
	  sf::Sprite 	title_sprite;
	  sf::Sprite 	play_button_sprite;
	public:
		MainMenuState		(GameDataRef _data);

		void init			();
		void handle_input	(float delta);
		void draw			(float delta);
		void update			(float delta){}
	};
}
#endif //MAINMENUSTATE_HPP