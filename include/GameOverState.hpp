#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP
#include "State.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>

namespace cp
{
	class GameOverState : public State {
		private:
		GameDataRef data;
		sf::Clock clock;
		sf::Sprite 	background_sprite;

		public:
		GameOverState		(GameDataRef _data);
		~GameOverState			();

		void init			();
		void handle_input	(float delta);
		void draw			(float delta);
		void update			(float delta);

		sf::Font font;
		sf::Text text;
	};
} // namespace cp

#endif //GAMEOVERSTATE_HPP