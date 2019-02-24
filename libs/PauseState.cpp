#include "PauseState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <sstream>

namespace cp
{
PauseState::PauseState(GameDataRef _data) : data(_data)
{
}
void PauseState::init()
{
	data->assets.load_texture("PlayButton", PLAY_BUTTON_FILEPATH);
	play_button_sprite.setTexture(data->assets.get_texture("PlayButton"));
	play_button_sprite.scale(Scaling_factor);
	data->assets.load_texture("GameOverState background", GAME_OVER_BACKGROUND_FILEPATH);
	font = data->assets.get_font("vfont");
	text.setFont(font);
	text.setString("Resume");
	text.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	play_button_sprite.setPosition(SCREEN_WIDTH / 2 - play_button_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - play_button_sprite.getGlobalBounds().height / 2);
}
void PauseState::handle_input(float delta)
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			data->window.close();
		}
		else if (data->input.is_sprite_clicked(play_button_sprite, sf::Mouse::Left, data->window))
		{
			std::cout << "Button is pressed" << std::endl;
			data->machine.remove_state();
		}
	}
}
void PauseState::draw(float delta)
{
	data->window.clear();
	data->window.draw(text);
	data->window.draw(play_button_sprite);
	data->window.display();
}
void PauseState::update(float delta)
{
}
} // namespace cp
