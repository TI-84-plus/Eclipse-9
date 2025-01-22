#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>  
#include <SFML/Window.hpp>
#include "Animation.hpp"
#include <iostream>

class Player
{
    private:
		enum dir {Moving_up = 0, Moving_Down = 0, Move_Right = 0, Move_Left = 0};

    public:
		sf::Sprite player_sprt;
		std::unique_ptr<sf::Texture> idle_txt;
		std::unique_ptr<sf::Texture> running_txt;
		std::vector<std::unique_ptr<sf::Texture>> textures;

		bool IsMovingUp = false;
		bool IsMovingDown = false;
		bool IsMovingRight = false;
		bool IsMovingLeft = false;

		std::map<std::string, int> PlayerStates 
		{
			{"idle_up", 5},
			{"idle_down", 6},
			{"idle_right", 7},
			{"idle_left", 8},
			
			{"running_up", 1},
			{"running_down", 2},
			{"running_right", 3},
			{"running_left", 4}
		};


		Animation animation{player_sprt, textures};

		int CurrentPlayerState = 0;

		sf::Vector2f position;

		int player_speed = 1;

		Player() {
			idle_txt = std::make_unique<sf::Texture>();
			idle_txt->loadFromFile("../../src/content/level1_idle.png");
			running_txt = std::make_unique<sf::Texture>();
			running_txt->loadFromFile("../../src/content/level1_running.png");
			
			textures.push_back(std::move(running_txt));
			textures.push_back(std::move(idle_txt));
			
			player_sprt.setScale(0.08, 0.08);
			animation.addFrame({sf::IntRect(8, 13, 63, 101), 6});
		}

		void UpdatePlayerStatus(sf::Event event) {
			if(event.type == event.KeyPressed) 
			{
				if(IsMovingUp) {
					CurrentPlayerState = PlayerStates["running_up"];
					player_sprt.setTexture(*textures[0]);
					animation.frames.clear();
					 animation.addFrame({sf::IntRect((88*0), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*1), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*2), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*3), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*4), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*5), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*6), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*7), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*8), 0, 63, 101), 6});
					 animation.addFrame({sf::IntRect((88*9), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*10), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*11), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*12), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*13), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*14), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*15), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*16), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*17), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*18), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*19), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*20), 0, 63, 101), 6});
					animation.addFrame({sf::IntRect((88*21), 0, 63, 101), 6});

				}

				else if(IsMovingDown) {
					CurrentPlayerState = PlayerStates["running_down"];
				}

				else if(IsMovingRight) {
					CurrentPlayerState = PlayerStates["running_right"];
				}

				else if(IsMovingLeft) {
					CurrentPlayerState = PlayerStates["running_left"];
				}
				std::cout<<CurrentPlayerState<<std::endl;
			}


			else if(event.type == event.KeyReleased)
			{
				player_sprt.setTexture(*textures[1]);
				if(CurrentPlayerState == PlayerStates["running_up"])
				{
					CurrentPlayerState = PlayerStates["idle_up"];
					animation.frames.clear();
					 animation.addFrame({sf::IntRect((92*0)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*1)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*2)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*3)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*4)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*5)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*6)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*7)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*8)+8, 11, 63, 101), 6});
					 animation.addFrame({sf::IntRect((92*9)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*10)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*11)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*12)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*13)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*14)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*15)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*16)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*17)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*18)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*19)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*20)+8, 11, 63, 101), 6});
					animation.addFrame({sf::IntRect((92*21)+8, 11, 63, 101), 6});
				}

				else if(CurrentPlayerState == PlayerStates["running_down"]) {
					CurrentPlayerState = PlayerStates["idle_down"];
					animation.frames.clear();	
					 animation.addFrame({sf::IntRect((92*0)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*1)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*2)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*3)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*4)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*5)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*6)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*7)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*8)+21, 463, 63, 108), 6});
					 animation.addFrame({sf::IntRect((92*9)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*10)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*11)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*12)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*13)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*14)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*15)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*16)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*17)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*18)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*19)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*20)+21, 463, 63, 108), 6});
					animation.addFrame({sf::IntRect((92*21)+21, 463, 63, 108), 6});
				}

				else if(CurrentPlayerState == PlayerStates["running_right"]) {
					CurrentPlayerState = PlayerStates["idle_right"];
					animation.frames.clear();	
					 animation.addFrame({sf::IntRect((92*0)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*1)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*2)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*3)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*4)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*5)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*6)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*7)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*8)+10, 239, 48, 101), 6});
					 animation.addFrame({sf::IntRect((92*9)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*10)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*11)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*12)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*13)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*14)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*15)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*16)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*17)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*18)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*19)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*20)+10, 239, 48, 101), 6});
					animation.addFrame({sf::IntRect((92*21)+10, 239, 48, 101), 6});
				}

				else if(CurrentPlayerState == PlayerStates["running_left"]) {
					CurrentPlayerState = PlayerStates["idle_left"];
					animation.frames.clear();	
						    animation.addFrame({sf::IntRect(34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*1)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*2)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*3)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*4)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*5)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*6)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*7)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*8)+34, 704, 48, 103), 6});
					 animation.addFrame({sf::IntRect((92*9)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*10)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*11)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*12)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*13)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*14)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*15)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*16)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*17)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*18)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*19)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*20)+34, 704, 48, 103), 6});
					animation.addFrame({sf::IntRect((92*21)+34, 704, 48, 103), 6});
				};
			};
			std::cout<<CurrentPlayerState<<std::endl;
		};

		// virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
		// {
		// 	states.texture = &player_txt;
		// 	target.draw(player_sprt, states);
        //     std::cout<<CurrentPlayerState<<std::endl;
		// }
		
};
#endif
