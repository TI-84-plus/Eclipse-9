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
            view.setCenter(1024, 1024);
            Game.player.player_sprt.setPosition(1024, 1024);
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
					Game.player.IsMovingUp = isPressed(event);
					Game.player.UpdatePlayerStatus(event);
					break;
				case sf::Keyboard::S:
					Game.player.IsMovingDown = isPressed(event);
					Game.player.UpdatePlayerStatus(event);
					break;
				case sf::Keyboard::A:
					Game.player.IsMovingLeft = isPressed(event);
					Game.player.UpdatePlayerStatus(event);
					break;
				case sf::Keyboard::D:
					Game.player.IsMovingRight = isPressed(event);
					Game.player.UpdatePlayerStatus(event);
					break;

			}

			//MouseWheel
			if(event.mouseWheelScroll.delta < 0) {
				double MapZoom = (MapZoom*1.1);

				view.zoom(1.1);
				std::cout<<view.getSize().x<<" "<<view.getSize().y<<std::endl;
            }
			
			if(event.mouseWheelScroll.delta > 0) {
				double MapZoom = (MapZoom*0.9);

				view.zoom(0.9);
				std::cout<<view.getSize().x<<" "<<view.getSize().y<<std::endl;
			}
		}

        void Update(StateManager* game) {

            //Up
            if(Game.player.IsMovingUp)
            {
                // Game.player.position.y -= Game.player.player_speed;	
				// view.setCenter(Game.player.position);
            }

            //Down
            if(Game.player.IsMovingDown) 
            {
                Game.player.position.y += Game.player.player_speed;		
				view.setCenter(Game.player.position);
            }

            //Right
            if(Game.player.IsMovingRight) 
            {
                Game.player.position.x += Game.player.player_speed;		
				view.setCenter(Game.player.position);
            }

            //Left
            if(Game.player.IsMovingLeft) 
            {
                Game.player.position.x -= Game.player.player_speed;		
				view.setCenter(Game.player.position);
				// std::cout<<"View: "<<view.getCenter().x<<" "<<view.getCenter().y<<std::endl;
				// std::cout<<"Player: "<<Game.player.position.x<<" "<<Game.player.position.y<<std::endl;
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
            
            Game.player.animation.update(1);
			renderer.draw(Game.player.player_sprt);
            renderer.display();
        };

};
#endif
