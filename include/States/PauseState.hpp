#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace cp {

class PauseState : public State{

  public:
	PauseState(GameDataRef _data);
	~PauseState();
	void init();
	void handle_input(float delta);
	void draw(float delta);
	void update(float delta);

  private:
	GameDataRef data;
	sf::Sprite background_sprite;
	sf::Sprite resume_button_sprite;
	sf::Font font;
	sf::Text text;
	};
}
#endif //PAUSESTATE_HPP