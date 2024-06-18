#ifndef MAPSELECTIONSTATE_H
#define MAPSELECTIONSTATE_H

#include <algorithm>
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
#include <ostream>
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
            view = sf::View(sf::FloatRect(800.f, 800.f, screenwidth, screenheight));
            view.setCenter(0,0);
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
                    mapselection.selected = isPressed;
                break;

            case sf::Keyboard::Space:
                    mapselection.MapGenerationRequested = isPressed;
            default:
                break;
        }
    }

    void handleInput(sf::Event key) 
    {
        switch (key.type) {
            case key.KeyReleased:
                processInput(key, false);
                break;

            case key.KeyPressed:
                processInput(key, true);
                break;
        };
    }
    
    void Update() {
        
         //Up
        if(mapselection.IsMovingUp)
        {
            float y = view.getCenter().x;
            y = std::clamp(y, -128.0f, 128.0f);
            view.setCenter(view.getCenter().x, y);
            std::cout<<view.getCenter().y<<std::endl;
            view.move(0, -mapselection.mov_speed);
        }

        //Down
        if(mapselection.IsMovingDown) 
        {
            float y = view.getCenter().x;
            y = std::clamp(y, -128.0f, 128.0f);
            view.setCenter(view.getCenter().x, y);
            std::cout<<view.getCenter().y<<std::endl;
            view.move(0, mapselection.mov_speed);
        }

        //Right
        if(mapselection.IsMovingRight) 
        {
            float x = view.getCenter().x;
            x = std::clamp(x, -32.0f, 32.0f);
            view.setCenter(x, view.getCenter().y);
            view.move(-mapselection.mov_speed, 0);
            std::cout<<view.getCenter().x<<std::endl;
        }

        //Left
        if(mapselection.IsMovingLeft)
        {
            float x = view.getCenter().x;
            x = std::clamp(x, -32.0f, 32.0f);
            view.setCenter(x, view.getCenter().y);
            view.move(mapselection.mov_speed, 0);
            std::cout<<view.getCenter().x<<std::endl;
        }

        //regenerate map
        if(mapselection.MapGenerationRequested) {
            chunks = mapselection.WorldGen();
            mapselection.MapGenerationRequested = false;
        }
    }


    void Render(renderer &render)
    {
        render.windows.clear();
        render.windows.setView(view);
        for(const Chunk& chunk : chunks)
        {
            render.windows.draw(chunk.sprite);
        }
        render.windows.display();
    }
};

#endif
