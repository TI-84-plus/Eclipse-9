#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>  
#include <SFML/Window.hpp>

class Player : public sf::Drawable
{
    private:
        enum dir {Moving_up = 0, Moving_Down = 0, Move_Right = 0, Move_Left = 0};

        sf::Texture txt;
        sf::Sprite sprt;

    public:
		bool IsMovingUp = false;
		bool IsMovingDown = false;
		bool IsMovingRight = false;
		bool IsMovingLeft = false;

		sf::Vector2f position;

		int player_speed = 32;

		Player() 
		{
			txt.create(20, 20);
			
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
		{
			states.texture = &txt;	
			target.draw(sprt, states);
		}
		
        void move() 
        {
                 
        }
};
#endif
