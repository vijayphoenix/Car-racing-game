#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP
#include "State.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>

namespace cp
{
	class SplashState : public State {
		private:
		GameDataRef 	data;
		sf::Clock 		clock;
		sf::Sprite 		background_sprite;
		bool timeover =false;
		public:
		SplashState			(GameDataRef _data);
		~SplashState		();

		void init			();
		void handle_input	(float delta);
		void draw			(float delta);
		void update			(float delta);
	};
}
#endif //SPLASHSTATE_HPP