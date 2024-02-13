#ifndef STATE_H
#define STATE_H

#include "SFML/Window/Event.hpp"
#include <iostream>

class State
{
public:
    virtual void Enter() = 0;

    virtual void Exit() = 0;

    virtual void handleInput(sf::Event event) = 0;

    virtual void Update() = 0;

    virtual void Render() = 0;
};

#endif
