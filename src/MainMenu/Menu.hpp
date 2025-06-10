#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "State/GameState.hpp"
#include "State/StateManager.hpp"


class options {
	
};

class Menu: public GameState {
	private:
		std::vector<options> menu_options;
		sf::Texture menu_texture;
		sf::Font menu_font;
		sf::Sprite menu_sprite;

		sf::Vector2i pos_mouse;
		

	public:
		Menu();
		void Pause();
		void Resume();

		void HandleInput(sf::Event event);
		void Update(StateManager* game);
		void Draw(sf::RenderWindow& renderer);
};


#endif
