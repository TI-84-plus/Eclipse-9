#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "Renderer/renderer.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include "InGame.h"
#include <ostream>

class InGameState: public GameState 
{
    private:
        int MapSeed;
        InGame Game{MapSeed};

    public:

        InGameState(int seed): MapSeed{seed}
        {
            view.zoom(8);
            std::cout<<"InGameState Seed:" <<MapSeed<<std::endl;
        }

        void Init() {};
        void Cleanup() {};

        void Pause() {};
        void Resume() {};

        bool isPressed(sf::Event event)
        {
            return event.type == event.KeyPressed;
        }


        void HandleInput(StateManager* game, sf::Event event) {

        switch (event.key.code)
        {
            case sf::Keyboard::W:
                Game.IsMovingUp = isPressed(event);
                break;
                
            case sf::Keyboard::S:
               Game.IsMovingDown = isPressed(event);
                break;

            case sf::Keyboard::A:
                Game.IsMovingRight = isPressed(event);
                break;

            case sf::Keyboard::D:
                Game.IsMovingLeft = isPressed(event);
                break;
            
            default:
                break;
        }
        };
        void Update(StateManager* game) {

            //Up
            if(Game.IsMovingUp)
            {
                // float y = view.getCenter().x;
                view.move(0, -Game.move_speed);
            }

            //Down
            if(Game.IsMovingDown) 
            {
                // float y = view.getCenter().x;
                view.move(0, Game.move_speed);
            }

            //Right
            if(Game.IsMovingRight) 
            {
                // float x = view.getCenter().x;
                view.move(-Game.move_speed, 0);
            }

            //Left
            if(Game.IsMovingLeft) 
            {
                // std::cout<<isPressed(event)<<std::endl;
                view.move(Game.move_speed, 0);
            }
        };

        void Draw(StateManager* game, sf::RenderWindow& renderer) {
            renderer.clear();
            renderer.setView(view);
            for(const TileMap& chunk : Game.map.ChunkArr) 
            {
                renderer.draw(chunk);
            }
            renderer.display();
        };



};
#endif
