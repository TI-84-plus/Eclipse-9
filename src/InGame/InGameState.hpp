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

        InGameState(int seed): MapSeed{seed}
        {
            view = sf::View(sf::FloatRect(800.f, 800.f, screenwidth, screenheight));
            std::cout<<"InGameState Seed:" <<MapSeed<<std::endl;
        }


        void Pause() {};
        void Resume() {};

        bool isPressed(sf::Event event)
        {
            return event.type == event.KeyPressed;
        }


        void HandleInput(StateManager* game, sf::Event event) 
		{   

			switch (event.key.code) {
				case sf::Keyboard::W:
					Game.IsMovingUp = isPressed(event);
					break;
				case sf::Keyboard::S:
					Game.IsMovingDown = isPressed(event);
					break;
				case sf::Keyboard::A:
					Game.IsMovingLeft = isPressed(event);
					break;
				case sf::Keyboard::D:
					Game.IsMovingRight = isPressed(event);
					break;

			}

			//MouseWheel
			if(event.mouseWheelScroll.delta < 0) {
				double MapZoom = (MapZoom*1.1);
                // zoom_x += 400;
                // zoom_y += 400; 
                //view.setSize(sf::Vector2f(zoom_x, zoom_y));

				view.zoom(1.1);
                //view.setSize(std::floor(view.getSize().x), std::floor(view.getSize().y));
				// std::cout<<MapZoom<<std::endl;
                // std::cout<<view.getCenter().x<<"    "<<view.getCenter().y<<std::endl;
				std::cout<<view.getSize().x<<" "<<view.getSize().y<<std::endl;
            }
			
			if(event.mouseWheelScroll.delta > 0) {
				double MapZoom = (MapZoom*0.9);
                // zoom_x -= 400;
                // zoom_y -= 400; 
                // view.setSize(sf::Vector2f(zoom_x, zoom_y)); 


				view.zoom(0.9);
                //view.setSize(std::floor(view.getSize().x), std::floor(view.getSize().y));
				//std::cout<<MapZoom<<std::endl;
                //std::cout<<view.getCenter().x<<"    "<<view.getCenter().y<<std::endl;
				std::cout<<view.getSize().x<<" "<<view.getSize().y<<std::endl;
			}
		}

        void Update(StateManager* game) {

            //Up
            if(Game.IsMovingUp)
            {
                // float y = view.getCenter().x;
                view.move(0.f, -Game.move_speed);
                std::cout<<view.getCenter().x<<" "<<view.getCenter().y<<std::endl;
            }

            //Down
            if(Game.IsMovingDown) 
            {
                // float y = view.getCenter().x;
                view.move(0.f, Game.move_speed);
                std::cout<<view.getCenter().x<<" "<<view.getCenter().y<<std::endl;
            }

            //Right
            if(Game.IsMovingRight) 
            {
                // float x = view.getCenter().x;
                view.move(Game.move_speed, 0.f);
                std::cout<<view.getCenter().x<<" "<<view.getCenter().y<<std::endl;
            }

            //Left
            if(Game.IsMovingLeft) 
            {
                // std::cout<<isPressed(event)<<std::endl;
                view.move(-Game.move_speed, 0.f);
                std::cout<<view.getCenter().x<<" "<<view.getCenter().y<<std::endl;
            }
        };

        void Draw(StateManager* game, sf::RenderWindow& renderer) {
            renderer.clear();
            //renderer.setView(game->GetActiveState()->view);
            renderer.setView(view);
            for(const TileMap& chunk : Game.map.ChunkArr) 
            {
                renderer.draw(chunk);
            }
            renderer.display();
        };

};
#endif
