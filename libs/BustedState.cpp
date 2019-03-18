#include "BustedState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <sstream>

namespace cp
{
BustedState::BustedState(GameDataRef _data) : data(_data)
{
}
void BustedState::init()
{
	data->assets.load_texture("GameOverState background", GAME_OVER_BACKGROUND_FILEPATH);
	background_sprite.setTexture(data->assets.get_texture("GameOverState background"));
	background_sprite.scale(1, 600.0f / 512.0f);
	background_sprite.setPosition(SCREEN_WIDTH / 2 - background_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2.1f - background_sprite.getGlobalBounds().height / 2);
    data->assets.load_texture("MenuButton", MENU_BUTTON_FILEPATH);
	menu_button_sprite.setTexture(data->assets.get_texture("MenuButton"));
	menu_button_sprite.scale(Scaling_factor/2.5f);
	menu_button_sprite.setPosition(SCREEN_WIDTH / 2 - menu_button_sprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - 2.3*menu_button_sprite.getGlobalBounds().height);
    menu_button_sprite.setColor(sf::Color(255,255,255,210));
}

void BustedState::draw(float delta)
{
	data->window.clear();
	data->window.draw(background_sprite);
    data->window.draw(menu_button_sprite);
	data->window.display();
}
void BustedState::update(float delta)
{
    
}
} // namespace cp
