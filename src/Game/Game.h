#ifndef GAME_H
#define GAME_H

#include "Renderer/renderer.h"
#include "MapSelection/MapSelectionState.h"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "State/State.hpp"
#include "State/StateManager.hpp"
#include <iostream>
#include <stack>
#include <memory>

class MapSelectionState;
class Game
{
private:
    renderer render; 
    //Game Runner
    bool IsRunning = true;
public:
    StateManager manager;

    Game() 
    {
        manager.CreateState<MapSelectionState>();
    }

    void Run()
    {
        while(IsRunning) 
        {
            Game::ProcessingInput();

            Game::Update();

            Game::Render();
        }
    }

    //Process Input
    void ProcessingInput()
    {
        sf::Event event;
        while (render.windows.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    IsRunning = false;
                    render.windows.close();
                    break;

                case sf::Event::Resized:
                    {sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    render.windows.setView(sf::View(visibleArea));
                    break;}

              default:
                    manager.States.top()->handleInput(event);
            }
        }
    }

    //Update
    void Update()
    {
        manager.States.top()->Update();
        sf::VertexArray(sf::Lines, 2);
    }

    //Render
    void Render()
    {
        manager.States.top()->Render(render);
    }
};
#endif
