#ifndef STATE_H
#define STATE_H

#include "Renderer/renderer.h"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>

class State
{
public:
    sf::View view;

    virtual void Enter() = 0;

    virtual void Exit() = 0;

    virtual void handleInput(sf::Event event) = 0;

    virtual void Update() = 0;

    virtual void Render(renderer &render) = 0;
};

#endif
