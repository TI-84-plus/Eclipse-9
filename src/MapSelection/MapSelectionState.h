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
#include "State/GameState.hpp"
#include "MapSelection/MapSelection.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ostream>
#include "State/StateManager.hpp"
#include "Test/Test.h"
#include "Renderer/renderer.h"

class game;
class MapSelectionState: public GameState 
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
    void Init() 
    {
        
    }

    void Cleanup(){}
    
    bool isPressed(sf::Event event)
    {
        return event.type == event.KeyPressed;
    }

    void HandleInput(StateManager* m_manager, sf::Event event) 
    {
        switch (event.key.code)
        {
            case sf::Keyboard::W:
                mapselection.IsMovingUp = isPressed(event);
                std::cout<<"State called"<<std::endl;
                break;
                
            case sf::Keyboard::S:
               mapselection.IsMovingDown = isPressed(event);
                break;

            case sf::Keyboard::A:
                mapselection.IsMovingRight = isPressed(event);
                break;

            case sf::Keyboard::D:
                mapselection.IsMovingLeft = isPressed(event);
                break;
            
            case sf::Keyboard::M:
                mapselection.NoBoundry = isPressed(event);
                break;

            case sf::Keyboard::Enter:
                    mapselection.selected = isPressed(event);
                break;

            case sf::Keyboard::Space:
                    mapselection.MapGenerationRequested = isPressed(event);
                break;
            
            default:
                break;
        }
    }
    
    void Update(StateManager* m_manager) {
        
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
        
        if(mapselection.selected) 
        {
            
        }
    }

    void Pause() {};
    void Resume() {};


    void Draw(StateManager* m_manager)
    {
        // render.windows.clear();
        // render.windows.setView(view);
        // for(const Chunk& chunk : chunks)
        // {
        //     render.windows.draw(chunk.sprite);
        // }
        // render.windows.display();
    }
};

#endif
