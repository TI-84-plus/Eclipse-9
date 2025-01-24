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

		int player_speed = 1;

		Player() {
			idle_txt = std::make_unique<sf::Texture>();
			idle_txt->loadFromFile("../../src/content/level1_idle.png");
			running_txt = std::make_unique<sf::Texture>();
			running_txt->loadFromFile("../../src/content/level1_running.png");
			
			textures.push_back(std::move(running_txt));
			textures.push_back(std::move(idle_txt));
			
			player_sprt.setScale(0.08, 0.08);

			animation.addFrame(92, 0, 92, 116, running_duration);	//idle up
			animation.addFrame(92, 464, 92, 116, running_duration); //idle down
			animation.addFrame(92, 232, 92, 116, running_duration);	//idle right
			animation.addFrame(92, 696, 92, 116, running_duration); //idle left

			animation.addFrame(88, 0, 88, 132, running_duration);	//running up
			animation.addFrame(88, 528, 88, 132, running_duration);	//running down
			animation.addFrame(88, 264, 88, 132, running_duration); //running right
			animation.addFrame(88, 792, 88, 132, running_duration); //running left
			
			animation.addFrame(92, 116, 92, 116, idle_duration);	//idle topRight
			animation.addFrame(92, 348, 92, 116, idle_duration);	//idle bottomRight
			animation.addFrame(92, 580, 92, 116, idle_duration);	//idle bottomLeft
			animation.addFrame(92, 812, 92, 116, idle_duration);	//idle topLeft

			animation.addFrame(88, 132, 92, 116, idle_duration);	//running topRight
			animation.addFrame(88, 396, 92, 116, idle_duration);	//running bottomRight
			animation.addFrame(88, 660, 92, 116, idle_duration);	//running bottomLeft
			animation.addFrame(88, 924, 92, 116, idle_duration);	//running topLeft

		}

		void UpdatePlayerStatus(sf::Event event) {
		if(IsMovingUp == 1 || IsMovingDown == 1 || IsMovingLeft == 1 || IsMovingRight == 1) 
			{
				player_sprt.setTexture(*textures[0]);
				if(IsMovingUp) {
					CurrentPlayerState = PlayerStates["running_up"];
					animation.currentFrame = 4;
				}

				else if(IsMovingUp && IsMovingRight) {
					CurrentPlayerState = PlayerStates["running_topRight"];
					animation.currentFrame = 12;
				}

				else if(IsMovingDown) {
					CurrentPlayerState = PlayerStates["running_down"];
					animation.currentFrame = 5;
				}

				else if(IsMovingDown && IsMovingRight) {
					CurrentPlayerState = PlayerStates["running_bottomRight"];
					animation.currentFrame = 13;
				}

				else if(IsMovingRight) {
					CurrentPlayerState = PlayerStates["running_right"];
					animation.currentFrame = 6;
				}

				else if(IsMovingDown && IsMovingLeft) {
					CurrentPlayerState = PlayerStates["running_bottomLeft"];
					animation.currentFrame = 14;
				}

				else if(IsMovingLeft) {
					CurrentPlayerState = PlayerStates["running_left"];
					animation.currentFrame = 7;
				}

				else if(IsMovingUp && IsMovingLeft) {
					CurrentPlayerState = PlayerStates["running_topLeft"];
					animation.currentFrame = 15;
				}
			}


			else if(IsMovingLeft == 0 && IsMovingRight == 0 && IsMovingDown == 0 && IsMovingUp == 0)
			{
				player_sprt.setTexture(*textures[1]);
				if(CurrentPlayerState == PlayerStates["running_up"])
				{
					CurrentPlayerState = PlayerStates["idle_up"];
					 animation.currentFrame = 0;
				}

				if(CurrentPlayerState == PlayerStates["running_topRight"])
				{
					CurrentPlayerState = PlayerStates["idle_topRight"];
					 animation.currentFrame = 8;
				}

				else if(CurrentPlayerState == PlayerStates["running_down"]) {
					CurrentPlayerState = PlayerStates["idle_down"];
					 animation.currentFrame = 1;
				}

				if(CurrentPlayerState == PlayerStates["running_bottomRight"])
				{
					CurrentPlayerState = PlayerStates["idle_bottomRight"];
					 animation.currentFrame = 9;
				}

				else if(CurrentPlayerState == PlayerStates["running_right"]) {
					CurrentPlayerState = PlayerStates["idle_right"];
					animation.currentFrame = 2;
				}

				if(CurrentPlayerState == PlayerStates["running_bottomLeft"])
				{
					CurrentPlayerState = PlayerStates["idle_bottomLeft"];
					 animation.currentFrame = 10;
				}

				else if(CurrentPlayerState == PlayerStates["running_left"]) {
					CurrentPlayerState = PlayerStates["idle_left"];
					animation.currentFrame = 3;
				}

				if(CurrentPlayerState == PlayerStates["running_topLeft"])
				{
					CurrentPlayerState = PlayerStates["idle_topLeft"];
					 animation.currentFrame = 11;
				}

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
