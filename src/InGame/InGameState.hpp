#ifndef INGAMESTATE_H
#define INGAMESTATE_H


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include "InGame.hpp"
#include <ostream>

class InGameState: public GameState 
{
    private:
        double MapZoom = 4;
        float zoom_x = 1000, zoom_y = 1000;
        int MapSeed;
        InGame Game{MapSeed};

    public:
        InGameState(int seed);


        void Pause();
        void Resume();
    
        bool isPressed(sf::Event event);
    
    
        void HandleInput(sf::Event event);
    
        void Update(StateManager* game);
    
        void Draw(sf::RenderWindow& renderer);
};
#endif
