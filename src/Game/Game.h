#ifndef GAME_H
#define GAME_H

#include "Renderer/renderer.h"
#include "MapSelection/MapSelectionState.h"
#include "State/State.hpp"
#include "State/StateManager.hpp"
#include <iostream>
#include <stack>
#include <memory>
#include <vector>

renderer render;

class MapSelectionState;
class Game
{
private:
    std::vector<Chunk> chunks;
    StateManager manager;
    //Game Runner
    bool IsRunning = true;
public:

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

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                // mapselection.MapGenerationRequested = true;
            }

            //Enter to select map
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                // mapselection.selected = true;
                // mapselection.isopen = false;
            }

        }
    }

    //Update
    void Update()
    {

        // // Map generation
        // if (mapselection.MapGenerationRequested) {
        //     chunks = mapselection.WorldGen();
        // }

        // if(mapselection.selected)
        // {
        //     //Map GameMap(mapselection.seed1);
        //     mapselection.selected = false;
        // }
    } 

    //Render
    void Render()
    {
    }
};
#endif
