#ifndef BUSTED_STATE_HPP
#define BUSTED_STATE_HPP
#include <SFML/Graphics.hpp>
#include "States/State.hpp"
#include "Game.hpp"

namespace cp {

class BustedState : public State{

  public:
	BustedState(GameDataRef _data);
	~BustedState();
	void init();
	void draw(float delta);
	void update(float delta);
	void handle_input(float delta) {
		sf::Event event;
		while (data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data->window.close();
			}
			else if (data->input.is_sprite_clicked(menu_button_sprite, sf::Mouse::Left, data->window))
			{
				std::cout << "Button is pressed" << std::endl;
				data->machine.remove_state();
			}
		}
	}

  private:
	GameDataRef data;
	sf::Sprite menu_button_sprite;
	sf::Sprite background_sprite;
	sf::Font font;
	sf::Text text;
	};
}
#endif //BUSTED_STATE_HPP