#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceManagers/InputManager.hpp"
#include "ResourceManagers/AssetManager.hpp"
#include "States/StateMachine.hpp"
#include "NetworkManager.hpp"

namespace cp
{
	struct GameData {
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
		NetworkManager Nmanager;
	};
	typedef std::shared_ptr<GameData>GameDataRef;

	class Game {
		private:
		sf::Clock 	clock;
		const float delta 	= 1.0f/60.0f;
		GameDataRef data	=std::make_shared<GameData>();

		void run	();

		public:
		Game		(int width,int height,std::string title);
		~Game		();
	};
}
#endif //GAME_HPP