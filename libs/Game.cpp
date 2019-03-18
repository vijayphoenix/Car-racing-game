/**
 * @file Game.cpp
 * @author Vijay
 * @brief Provide all the game play resources to play the game and all provides cpu time to different states.
 * @version 0.1
 * @date 2019-03-01
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "Game.hpp"
#include "States/SplashState.hpp"

namespace cp
{
	/**
	 * @brief Construct a new Game:: Game object
	 *
	 * @param width Width of the screen requested.
	 * @param height Height of the screen requested.
	 * @param title Title of the game screen.
	 */
	Game::Game(int width, int height, std::string title) {
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		data->machine.add_state(StateRef(new SplashState(data)));
		data->window.setFramerateLimit(80);
		run();
	}
	/**
	 * @brief Destroy the Game:: Game object
	 *
	 */
	Game::~Game() {
	}
	/**
	 * @brief Runs a state at the top of the state machine.
	 *
	 */
	void Game::run() {
		float new_time, frame_time, interpolation;
		float current_time = clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (data->window.isOpen())
		{
			data->machine.process_state_change();
			new_time = clock.getElapsedTime().asSeconds();
			frame_time = new_time - current_time;
			if (frame_time > 0.25f)	frame_time = 0.25f;
			current_time = new_time;
			accumulator += frame_time;

			while (accumulator >= delta)
			{
				data->machine.get_active_state()->handle_input(delta);
				data->machine.get_active_state()->update(delta);
				accumulator -= delta;
			}
			interpolation = accumulator / delta;
			data->machine.get_active_state()->draw(interpolation);
		}
	}
}
