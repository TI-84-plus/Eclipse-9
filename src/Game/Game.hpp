#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "MapSelection/MapSelectionState.hpp"
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include <chrono>
#include <string>


class MapSelectionState;
class Game
{
private:
    sf::RenderWindow render = sf::RenderWindow(sf::VideoMode(screenwidth, screenheight), "Procedural generation");
    
    //Game Runner
    bool IsRunning = true;
    StateManager manager;


	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	float fps;
    sf::Text fpsT;
    sf::Font font;

public:

    Game() 
    {
        render.setVerticalSyncEnabled(false);
        manager.AddState(std::make_unique<InGameState>(int(123)), true);
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
        start = std::chrono::high_resolution_clock::now();
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
                    {sf::FloatRect visibleArea(event.size.width, event.size.height, event.size.width, event.size.height);
                    render.setView(sf::View(visibleArea));
                    break;}

				case sf::Event::KeyPressed:
                    manager.GetActiveState()->HandleInput(&manager, event);

                case sf::Event::KeyReleased:
                    manager.GetActiveState()->HandleInput(&manager, event);

				case sf::Event::MouseWheelScrolled:
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
        end = std::chrono::high_resolution_clock::now();
        fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        // std::cout<<fps<<std::endl;

    };
};
#endif
