#ifndef GAME_H
#define GAME_H

#include "MapSelection/MapSelection.h"
#include "Renderer/renderer.h"
#include "Map/Map.h"
#include "Test/Test.h"

class Game
{
private:
    renderer render;
    std::vector<Chunk> chunks;

    //Game Runner
    bool IsRunning = true;
public:
    MapSelection mapselection;

    void Run() 
    {
        mapselection.MapGenerationRequested = true;
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
                case sf::Event::KeyPressed:
                    HandlePlayerInput(event.key.code, true);
                    break;

                case sf::Event::KeyReleased:
                    HandlePlayerInput(event.key.code, false);
                    break;

                case sf::Event::Closed:
                    IsRunning = false;
                    render.windows.close();
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                mapselection.MapGenerationRequested = true;
            }

            //Enter to select map
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                mapselection.selected = true;
                mapselection.isopen = false;
            }

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                render.windows.setView(sf::View(visibleArea));
            }
        }
    }

    //Handle input
    void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {
        if(mapselection.isopen == true)
        {
            //MenuMap Directions
            switch (key)
            {
                case sf::Keyboard::W:
                    mapselection.IsMovingUp = isPressed;
                    break;

                case sf::Keyboard::S:
                    mapselection.IsMovingDown = isPressed;
                    break;

                case sf::Keyboard::A:
                    mapselection.IsMovingRight = isPressed;
                    break;

                case sf::Keyboard::D:
                    mapselection.IsMovingLeft = isPressed;
                    break;
                
                case sf::Keyboard::M:
                    mapselection.NoBoundry = isPressed;
                    break;
                default:
                    break;
            }
        }
        else 
        {
            //InGame Directions
            if(key == sf::Keyboard::W) 
            {
                
            }
        }

    }
    //Update
    void Update()
    {
        //Up
        if(mapselection.IsMovingUp)
        {
            if(mapselection.view.getCenter().y >= -((chunkSize*screen_height)/2)/2.2 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                mapselection.view.move(0, -mapselection.mov_speed);
            }
            
            mapselection.displayposition();
        }

        //Down
        if(mapselection.IsMovingDown) 
        {
            if(mapselection.view.getCenter().y <= ((chunkSize*screen_height)/2)/2.2 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                mapselection.view.move(0, mapselection.mov_speed);
            }
            
            mapselection.displayposition();
        }

        //Right
        if(mapselection.IsMovingRight) 
        {
            if(mapselection.view.getCenter().x > -((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                mapselection.view.move(-mapselection.mov_speed, 0);
            }
            mapselection.displayposition();
        }

        //Left
        if(mapselection.IsMovingLeft)
        {
            if(mapselection.view.getCenter().x < ((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                mapselection.view.move(mapselection.mov_speed, 0);
            }
            mapselection.displayposition();
        }

        // Map generation
        if (mapselection.MapGenerationRequested) {
            chunks = mapselection.WorldGen();
        }

        if(mapselection.selected)
        {
            //Map GameMap(mapselection.seed1);
            mapselection.selected = false;
        }
    } 

    //Render
    void Render()
    {
        render.windows.clear();
        render.windows.setView(mapselection.view);
        for(Chunk const &chunk : chunks) 
        {
            render.windows.draw(chunk.sprite);
        }
        render.windows.display();
    }
};
#endif
