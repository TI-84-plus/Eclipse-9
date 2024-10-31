#ifndef GAME_H
#define GAME_H

#include "Renderer/renderer.h"
#include "MapSelection/MapSelectionState.h"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include <iostream>
#include <stack>
#include <memory>

class MapSelectionState;
class Game
{
private:
    sf::RenderWindow render = sf::RenderWindow(sf::VideoMode(screenwidth, screenheight), "Procedural generation");
    
    //Game Runner
    bool IsRunning = true;
    StateManager manager;
public:

    Game() 
    {
        render.setVerticalSyncEnabled(true);
        manager.AddState(std::make_unique<MapSelectionState>(), true);
        manager.ProcessStateChanges();
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
        while (render.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    IsRunning = false;
                    render.close();
                    break;

                case sf::Event::Resized:
                    {sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    render.setView(sf::View(visibleArea));
                    break;}

                default:
                    manager.GetActiveState()->HandleInput(&manager, event);
            }
        }
    }

    //Update
    void Update()
    {
        manager.GetActiveState()->Update(&manager);
    }

    //Render
    void Render()
    {
        manager.GetActiveState()->Draw(&manager, render);
    };
};
#endif
