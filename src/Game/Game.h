#ifndef GAME_H
#define GAME_H

#include "MenuMap/MenuMap.h"
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
    MenuMap menumap;

    void Run() 
    {
        menumap.MapGenerationRequested = true;
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
                menumap.MapGenerationRequested = true;
            }

            //Enter to select map
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                menumap.selected = true;
                menumap.isopen = false;
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
        if(menumap.isopen == true)
        {
            //MenuMap Directions
            switch (key)
            {
                case sf::Keyboard::W:
                    menumap.IsMovingUp = isPressed;
                    break;

                case sf::Keyboard::S:
                    menumap.IsMovingDown = isPressed;
                    break;

                case sf::Keyboard::A:
                    menumap.IsMovingRight = isPressed;
                    break;

                case sf::Keyboard::D:
                    menumap.IsMovingLeft = isPressed;
                    break;
                
                case sf::Keyboard::M:
                    menumap.NoBoundry = isPressed;
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
        if(menumap.IsMovingUp)
        {
            if(menumap.view.getCenter().y >= -((chunkSize*screen_height)/2)/2.2 || (Test::MMLimiter == true && menumap.NoBoundry == true))
            {
                menumap.view.move(0, -menumap.mov_speed);
            }
            
            menumap.displayposition();
        }

        //Down
        if(menumap.IsMovingDown) 
        {
            if(menumap.view.getCenter().y <= ((chunkSize*screen_height)/2)/2.2 || (Test::MMLimiter == true && menumap.NoBoundry == true))
            {
                menumap.view.move(0, menumap.mov_speed);
            }
            
            menumap.displayposition();
        }

        //Right
        if(menumap.IsMovingRight) 
        {
            if(menumap.view.getCenter().x > -((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && menumap.NoBoundry == true))
            {
                menumap.view.move(-menumap.mov_speed, 0);
            }
            menumap.displayposition();
        }

        //Left
        if(menumap.IsMovingLeft)
        {
            if(menumap.view.getCenter().x < ((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && menumap.NoBoundry == true))
            {
                menumap.view.move(menumap.mov_speed, 0);
            }
            menumap.displayposition();
        }

        // Map generation
        if (menumap.MapGenerationRequested) {
            chunks = menumap.WorldGen();
        }

        if(menumap.selected)
        {
            //Map GameMap(menumap.seed1);
            menumap.selected = false;
        }
    } 

    //Render
    void Render()
    {
        render.windows.clear();
        render.windows.setView(menumap.view);
        for(Chunk const &chunk : chunks) 
        {
            render.windows.draw(chunk.sprite);
        }
        render.windows.display();
    }
};
#endif
