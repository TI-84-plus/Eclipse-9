#ifndef MAPSELECTIONSTATE_H
#define MAPSELECTIONSTATE_H

#include <cstdio>
#include <iostream>
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "State/State.hpp"
#include "MapSelection/MapSelection.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Test/Test.h"
#include "Renderer/renderer.h"

class Game;
class MapSelectionState : public State 
{
    private:
        extern renderer render;
    	MapSelection mapselection;
        std::vector<Chunk> chunks = mapselection.WorldGen();
    public:
    //Initialize resources
    void Enter() 
    {
        
    }

    void Exit(){}

    void processInput(sf::Event event, bool isPressed) 
    {
        //MenuMap Directions
        switch (event.key.code)
        {
            case sf::Keyboard::W:
                mapselection.IsMovingUp = isPressed;
                std::cout<<"State called"<<std::endl;
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

            case sf::Keyboard::Enter:

                break;

            case sf::Keyboard::Space:
                    
            default:
                break;
        }
    }

    void handleInput(sf::Event key) 
    {
        switch (key.type) {
            case key.KeyReleased:
                processInput(key, true);
                break;

            case key.KeyPressed:
                processInput(key, false);
                break;
        };
    }
    
    void Update() {
        
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
            if(mapselection.view.getCenter().x >= -((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                mapselection.view.move(-mapselection.mov_speed, 0);
            }

            mapselection.displayposition();
        }

        //Left
        if(mapselection.IsMovingLeft)
        {
            if(mapselection.view.getCenter().x <= ((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                mapselection.view.move(mapselection.mov_speed, 0);
            }

            mapselection.displayposition();
        }
    }


    void Render()
    {
        render.windows.clear();
        // render.windows.setView(mapselection.view);
        for(Chunk const &chunk : chunks)
        {
            render.windows.draw(chunk.sprite);
        }
        render.windows.display();
    }
};

#endif
