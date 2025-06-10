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

		double running_duration = 1;
		double idle_duration = 10;

		std::map<std::string, int> PlayerStates 
		{
			{"idle_up", 5},
			{"idle_down", 6},
			{"idle_right", 7},
			{"idle_left", 8},

			{"idle_topRight", 9},
			{"idle_bottomRight", 10},
			{"idle_bottomLeft", 11},
			{"idle_topLeft", 12},
			


			{"running_up", 1},
			{"running_down", 2},
			{"running_right", 3},
			{"running_left", 4},

			{"runnin_topRight", 13},
			{"running_bottomRight", 14},
			{"running_bottomLeft", 15},
			{"running_topLeft", 16}	
		};


		Animation animation{player_sprt, textures};

		int CurrentPlayerState = 6;

		sf::Vector2f position;
		sf::Vector2f world_position;
		sf::Vector2f grid_position;
		double player_speed = 1;	

		Player();

		void UpdatePlayerStatus(sf::Event event);

};
#endif
