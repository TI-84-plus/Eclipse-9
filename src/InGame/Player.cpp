#include "InGame/Player.hpp"



Player::Player() {
	idle_txt = std::make_unique<sf::Texture>();
	idle_txt->loadFromFile("assets/level1_idle.png");
	running_txt = std::make_unique<sf::Texture>();
	running_txt->loadFromFile("assets/level1_running.png");
	std::cout<<"Player constructor"<<std::endl;
	
	textures.push_back(std::move(running_txt));
	textures.push_back(std::move(idle_txt));
	player_sprt.setScale(1.0/92.f, 1.3/116.f);
	
	animation.addFrame(92, 0, 92, 116, idle_duration);	//idle up
	animation.addFrame(92, 464, 92, 116, idle_duration); //idle down
	animation.addFrame(92, 232, 92, 116, idle_duration);	//idle right
	animation.addFrame(92, 696, 92, 116, idle_duration); //idle lef

	animation.addFrame(88, 0, 88, 132, running_duration);	//running up
	animation.addFrame(88, 528, 88, 132, running_duration);	//running down
	animation.addFrame(88, 264, 88, 132, running_duration); //running right
	animation.addFrame(88, 792, 88, 132, running_duration); //running left
	
	animation.addFrame(92, 116, 92, 116, idle_duration);	//idle topRight
	animation.addFrame(92, 348, 92, 116, idle_duration);	//idle bottomRight
	animation.addFrame(92, 580, 92, 116, idle_duration);	//idle bottomLeft
	animation.addFrame(92, 812, 92, 116, idle_duration);	//idle topLef

	animation.addFrame(88, 132, 92, 116, running_duration);	//running topRight
	animation.addFrame(88, 396, 92, 116, running_duration);	//running bottomRight
	animation.addFrame(88, 660, 92, 116, running_duration);	//running bottomLeft
	animation.addFrame(88, 924, 92, 116, running_duration);	//running topLef
}

void Player::update(float deltaTime) {
    sf::Vector2f velocity(0, 0);
    
    // Calculate movement direction based on input
    if (IsMovingUp) velocity.y -= player_speed;
    if (IsMovingDown) velocity.y += player_speed;
    if (IsMovingLeft) velocity.x -= player_speed;
    if (IsMovingRight) velocity.x += player_speed;
    
    // Normalize diagonal movement to maintain consistent speed
    if (velocity.x != 0 && velocity.y != 0) {
        float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x = (velocity.x / length) * player_speed;
        velocity.y = (velocity.y / length) * player_speed;
    }
    
    // Apply movement with delta time
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    // Update sprite position
    player_sprt.setPosition(position);
    
    // Update world and grid positions
    world_position = position;
    grid_position.x = std::floor(position.x);
    grid_position.y = std::floor(position.y);
}

void Player::UpdatePlayerStatus(sf::Event event) 
{
	if(IsMovingUp == 1 || IsMovingDown == 1 || IsMovingLeft == 1 || IsMovingRight == 1) 
		{
			//std::cout<<position.x<<" "<<position.y<<std::endl;
			player_sprt.setTexture(*textures[0]);
			//Running Top
			if(IsMovingUp && !IsMovingDown && !IsMovingLeft && !IsMovingRight) {
				CurrentPlayerState = PlayerStates["running_up"];
				animation.currentFrame = 4;
			}

			//Running Up Right
			else if(IsMovingUp && IsMovingRight && !IsMovingLeft && !IsMovingDown) {
				CurrentPlayerState = PlayerStates["running_topRight"];
				animation.currentFrame = 12;
			}

			//Running Down
			else if(IsMovingDown && !IsMovingUp && !IsMovingLeft && !IsMovingRight) {
				CurrentPlayerState = PlayerStates["running_down"];
				animation.currentFrame = 5;
			}

			//Running Down Right
			else if(IsMovingDown && IsMovingRight && !IsMovingLeft && !IsMovingUp) {
				CurrentPlayerState = PlayerStates["running_bottomRight"];
				animation.currentFrame = 13;
			}

			//Running Right
			else if(IsMovingRight && !IsMovingUp &&!IsMovingDown &&!IsMovingLeft) {
				CurrentPlayerState = PlayerStates["running_right"];
				animation.currentFrame = 6;
			}

			//Running Down Left
			else if(IsMovingDown && IsMovingLeft &&!IsMovingUp &&!IsMovingRight) {
				CurrentPlayerState = PlayerStates["running_bottomLeft"];
				animation.currentFrame = 14;
			}

			//Running Left
			else if(IsMovingLeft &&!IsMovingRight &&!IsMovingUp &&!IsMovingDown) {
				CurrentPlayerState = PlayerStates["running_left"];
				animation.currentFrame = 7;
			}

			//Running up Left
			else if(IsMovingUp && IsMovingLeft &&!IsMovingDown &&!IsMovingRight) {
				CurrentPlayerState = PlayerStates["running_topLeft"];
				animation.currentFrame = 15;
			}
		}

	else if(IsMovingLeft == 0 && IsMovingRight == 0 && IsMovingDown == 0 && IsMovingUp == 0)
		{
			//std::cout<<position.x<<" "<<position.y<<std::endl;
			player_sprt.setTexture(*textures[1]);
			if(CurrentPlayerState == PlayerStates["running_up"])
			{
				CurrentPlayerState = PlayerStates["idle_up"];
				 animation.currentFrame = 0;
			}
			else if(CurrentPlayerState == PlayerStates["running_topRight"])
			{
				CurrentPlayerState = PlayerStates["idle_topRight"];
				 animation.currentFrame = 8;
			}	
			else if(CurrentPlayerState == PlayerStates["running_down"]) 
			{
				CurrentPlayerState = PlayerStates["idle_down"];
				 animation.currentFrame = 1;
			}
			else if(CurrentPlayerState == PlayerStates["running_bottomRight"])
			{
				CurrentPlayerState = PlayerStates["idle_bottomRight"];
				 animation.currentFrame = 9;
			}
			else if(CurrentPlayerState == PlayerStates["running_right"]) {
				CurrentPlayerState = PlayerStates["idle_right"];
				animation.currentFrame = 2;
			}
			else if(CurrentPlayerState == PlayerStates["running_bottomLeft"])
			{
				CurrentPlayerState = PlayerStates["idle_bottomLeft"];
				 animation.currentFrame = 10;
			}
			else if(CurrentPlayerState == PlayerStates["running_left"]) {
				CurrentPlayerState = PlayerStates["idle_left"];
				animation.currentFrame = 3;
			}
			else if(CurrentPlayerState == PlayerStates["running_topLeft"])
			{
				CurrentPlayerState = PlayerStates["idle_topLeft"];
				 animation.currentFrame = 11;
			}	
		};
};
