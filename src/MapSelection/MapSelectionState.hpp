#ifndef MAPSELECTIONSTATE_H
#define MAPSELECTIONSTATE_H


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <algorithm>
#include <cctype>
#include "InGame/InGameState.hpp"
#include "chunk.hpp"
#include "MapSelection.hpp"
#include "State/StateManager.hpp"


class game;
class MapSelectionState: public GameState 
{
    private:
        MapSelection mapselection;
    public:
        std::vector<Chunk> chunks;
		Chunk DrawChunk; 
        MapSelectionState() {

            chunks = mapselection.WorldGen();
            view = sf::View(sf::FloatRect(800.f, 800.f, screenwidth, screenheight));
            view.setCenter(0,0);
        };


    bool isPressed(sf::Event event)
    {
        return event.type == event.KeyPressed;
    }


    void HandleInput(sf::Event event) 
    {
        switch (event.key.code)
        {
            case sf::Keyboard::W:
                mapselection.IsMovingUp = isPressed(event);
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
            view.move(0, -mapselection.mov_speed);
        }

        //Down
        if(mapselection.IsMovingDown) 
        {
            float y = view.getCenter().x;
            y = std::clamp(y, -128.0f, 128.0f);
            view.setCenter(view.getCenter().x, y);
            view.move(0, mapselection.mov_speed);
        }

        //Right
        if(mapselection.IsMovingRight) 
        {
            float x = view.getCenter().x;
            x = std::clamp(x, -32.0f, 32.0f);
            view.setCenter(x, view.getCenter().y);
            view.move(-mapselection.mov_speed, 0);
        }

        //Left
        if(mapselection.IsMovingLeft)
        {
            float x = view.getCenter().x;
            x = std::clamp(x, -32.0f, 32.0f);
            view.setCenter(x, view.getCenter().y);
            view.move(mapselection.mov_speed, 0);
        }

        //regenerate map
        if(mapselection.MapGenerationRequested) {
            chunks = mapselection.WorldGen();
            mapselection.MapGenerationRequested = false;
        }
        
        if(mapselection.selected) 
        {
            m_manager->AddState(std::make_unique<InGameState>(int(mapselection.seed)), false);
            m_manager->ProcessStateChanges();
        }

    }

    void Pause() {};
    void Resume() {};


    void Draw(sf::RenderWindow& renderer)
    {
        renderer.clear();
        renderer.setView(view);
        for(const Chunk& chunk : chunks)
        {
            renderer.draw(chunk.sprite);
        }
        renderer.display();
    }
};

#endif
