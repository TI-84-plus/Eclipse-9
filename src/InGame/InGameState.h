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
            std::cout<<"InGameState Seed:" <<MapSeed<<std::endl;
        }

        void Init() {};
        void Cleanup() {};

        void Pause() {};
        void Resume() {};

        void HandleInput(StateManager* game, sf::Event event) {

        switch (event.key.code)
        {
            case sf::Keyboard::W:
            break;
            
            default:
                break;
        }
        };
        void Update(StateManager* game) {};

        void Draw(StateManager* game, sf::RenderWindow& renderer) {
            renderer.clear();
            renderer.draw(Game.map.map);
            renderer.display();
        };



};
#endif
