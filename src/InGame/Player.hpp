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
		sf::Texture player_txt;

		bool IsMovingUp = false;
		bool IsMovingDown = false;
		bool IsMovingRight = false;
		bool IsMovingLeft = false;

		Animation animation{player_sprt, player_txt};

		int txt_x = 92, start = 8;
		int CurrentPlayerState = 0;

		sf::Vector2f position;

		int player_speed = 32;

		Player() {
			player_txt.loadFromFile("../../src/content/level1_idle.png");
			animation.addFrame({sf::IntRect(8, 13, 63, 101), 6});

		}

		void UpdatePlayerStatus(sf::Event event) {
			if(event.type == event.KeyPressed) {
				if(IsMovingUp) {
					CurrentPlayerState = 1;
				}

				else if(IsMovingDown) {
					CurrentPlayerState = 2;
				}

				else if(IsMovingRight) {
					CurrentPlayerState = 3;
				}

				else if(IsMovingLeft) {
					CurrentPlayerState = 4;
				}
				std::cout<<CurrentPlayerState<<std::endl;
			}

			else if(event.type == event.KeyReleased){
				if(CurrentPlayerState == 1){
					CurrentPlayerState = 5;
						       animation.addFrame({sf::IntRect(8, 13, 63, 101), 30});
					 animation.addFrame({sf::IntRect((txt_x*1)+8, 13, 63, 101), 6});
					 animation.addFrame({sf::IntRect((txt_x*2)+8, 13, 63, 101), 6});
					 animation.addFrame({sf::IntRect((txt_x*3)+8, 13, 81, 113), 70});
					 animation.addFrame({sf::IntRect((txt_x*4)+8, 13, 81, 113), 6});
					 animation.addFrame({sf::IntRect((txt_x*5)+8, 13, 81, 113), 32});
					 animation.addFrame({sf::IntRect((txt_x*6)+8, 13, 81, 113), 6});
					 animation.addFrame({sf::IntRect((txt_x*7)+8, 13, 81, 113), 50});
					 animation.addFrame({sf::IntRect((txt_x*8)+8, 13, 81, 113), 6});
					 animation.addFrame({sf::IntRect((txt_x*9)+8, 13, 81, 113), 21});
					animation.addFrame({sf::IntRect((txt_x*10)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*11)+8, 13, 81, 113), 89});
					animation.addFrame({sf::IntRect((txt_x*12)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*13)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*14)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*15)+8, 13, 81, 113), 100});
					animation.addFrame({sf::IntRect((txt_x*16)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*17)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*18)+8, 13, 81, 113), 56});
					animation.addFrame({sf::IntRect((txt_x*19)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*20)+8, 13, 81, 113), 6});
					animation.addFrame({sf::IntRect((txt_x*21)+8, 13, 81, 113), 91});
				}

				else if(CurrentPlayerState == 2) {
					CurrentPlayerState = 6;
				}

				else if(CurrentPlayerState == 3) {
					CurrentPlayerState = 7;
				}

				else if(CurrentPlayerState == 4) {
					CurrentPlayerState = 8;
				};
			};
			std::cout<<CurrentPlayerState<<std::endl;
		};

		// virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
		// {
		// 	animation.update(1);
		// 	states.texture = &player_txt;
		// 	target.draw(player_sprt, states);
        //     std::cout<<CurrentPlayerState<<std::endl;
		// }
		
};
#endif
