#include "States/PauseState.hpp"
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
	background_sprite.setTexture(data->assets.get_texture("MainMenuStateBackground"));
	background_sprite.scale(1, 600.0f / 512.0f);
	background_sprite.setPosition(SCREEN_WIDTH / 2 - background_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2.1f - background_sprite.getGlobalBounds().height / 2);
	data->assets.load_texture("PlayButton3", RESUME_BUTTON_FILEPATH);
	resume_button_sprite.setTexture(data->assets.get_texture("PlayButton3"));
	resume_button_sprite.scale(Scaling_factor/2.f);
	data->assets.load_texture("GameOverState background", GAME_OVER_BACKGROUND_FILEPATH);
	// font = data->assets.get_font("vfont");
	// text.setFont(font);
	// text.setString("Resume");
	// text.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
	// text.setCharacterSize(24);
	// text.setFillColor(sf::Color::Red);
	// text.setStyle(sf::Text::Bold);
	resume_button_sprite.setPosition(SCREEN_WIDTH / 2 - resume_button_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - resume_button_sprite.getGlobalBounds().height / 2);
	resume_button_sprite.setColor(sf::Color(255,255,255,220));
	data->window.draw(resume_button_sprite);
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
		else if (data->input.is_sprite_clicked(resume_button_sprite, sf::Mouse::Left, data->window))
		{
			std::cout << "Button is pressed" << std::endl;
			data->machine.remove_state();
		}
	}
}
void PauseState::draw(float delta)
{
	data->window.clear();
	data->window.draw(background_sprite);
	data->window.draw(text);
	data->window.draw(resume_button_sprite);
	data->window.display();
}
void PauseState::update(float delta)
{
}
} // namespace cp
