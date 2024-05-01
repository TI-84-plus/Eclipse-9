#ifndef MAPSELECTIONSTATE_H
#define MAPSELECTIONSTATE_H

#include <cctype>
#include <cstdint>
#include <iostream>
#include "MapSelection/chunk.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/View.hpp"
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

class game;
class MapSelectionState: public State 
{
    private:
        MapSelection mapselection;
    public:
        std::vector<Chunk> chunks;
        MapSelectionState() {
            chunks = mapselection.WorldGen();
            std::cout<<"Constructor "<<unsigned(chunks[0].pixels[0])<<std::endl;
            view = sf::View(sf::FloatRect(500.f, 500.f, screenwidth, screenheight));
        };

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
            if(view.getCenter().y >= -((chunkSize*screen_height)/2)/2.2 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
               view.move(0, -mapselection.mov_speed);
            }
        }

        //Down
        if(mapselection.IsMovingDown) 
        {
            if(view.getCenter().y <= ((chunkSize*screen_height)/2)/2.2 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                view.move(0, mapselection.mov_speed);
            }
        }

        //Right
        if(mapselection.IsMovingRight) 
        {
            if(view.getCenter().x >= -((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                view.move(-mapselection.mov_speed, 0);
            }
        }

        //Left
        if(mapselection.IsMovingLeft)
        {
            if(view.getCenter().x <= ((chunkSize*screen_width)/2)/16 || (Test::MMLimiter == true && mapselection.NoBoundry == true))
            {
                view.move(mapselection.mov_speed, 0);
            }
        }
    }


    void Render(renderer &render)
    {
        render.windows.clear(sf::Color::Red);
        render.windows.setView(view);
        for(Chunk const &chunk : chunks)
        {
            std::cout<<"Render "<<unsigned(chunks[0].pixels[0]);
            //std::cout<<"Chunk added"<<std::endl;
            render.windows.draw(chunk.sprite);
        }
        render.windows.display();
    }
};

#endif
