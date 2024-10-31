#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Renderer/renderer.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>

class StateManager;
class GameState
{
public:
    sf::View view;

    virtual void Init() = 0;
    virtual void Cleanup() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleInput(StateManager* game, sf::Event event) = 0;
    virtual void Update(StateManager* game) = 0;
    virtual void Draw(StateManager* game, sf::RenderWindow& renderer) = 0;
};

#endif
