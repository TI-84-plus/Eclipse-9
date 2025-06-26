#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include "MapSelection/MapSelectionState.hpp"



class Menu: public GameState {
	private:
		enum MenuButtonType {
			NEW_GAME,
			LOAD,
			OPTIONS,
			EXIT,
			BUTTONS_COUNT
		};
		bool hover_NEW_GAME = false;
		bool hover_LOAD = false;
		bool hover_OPTIONS = false;
		bool hover_EXIT = false;

		bool trigger_NEW_GAME = false;


		std::vector<sf::Sprite> MenuButtons;
		sf::Texture menu_texture_idle;
		sf::Texture menu_texture_hover;
		sf::Font menu_font;
		sf::Sprite menu_sprite;

		sf::Vector2i pos_mouse;
		

	public:
		Menu();
		void Pause();
		void Resume();

		void HandleInput(sf::Event event) override;
		void HandleInput(sf::Event event, sf::RenderWindow& render);
		void Update(StateManager* game, float deltaTime);
		void Draw(sf::RenderWindow& renderer);
};


#endif
