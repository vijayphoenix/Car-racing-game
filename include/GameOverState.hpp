#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace cp
{
	class GameOverState : public State
	{
	private:
		GameDataRef data;
		sf::Sprite background_sprite;

	public:
		GameOverState(GameDataRef _data);
		// ~GameState();

		void init();
		void handle_input();
		void draw(float delta);
		void update(float delta);
	};
} // namespace cp

#endif //GAMEOVERSTATE_HPP