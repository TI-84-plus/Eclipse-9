#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"

class StateManager;
class GameState
{
public:

    virtual ~GameState() = default;

	const int screenwidth = 1920;
	const int screenheight = 1080;
	
    sf::View view;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleInput(sf::Event event) = 0;
    virtual void Update(StateManager* game, float deltaTime) = 0;
    virtual void Draw(sf::RenderWindow& renderer) = 0;
};

#endif
