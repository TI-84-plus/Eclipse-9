#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>  
#include <SFML/Window.hpp>

class player
{
    private:
        enum dir {Moving_up = 0, Moving_Down = 0, Move_Right = 0, Move_Left = 0};
        sf::Texture txt;
        sf::Sprite  sprt;
        sf::Uint8   pos;

    public:
        void move() 
        {
                 
        }
};
    

#endif