#include "InGameState.hpp"

InGameState::InGameState(int seed): MapSeed{seed}
{
	view = sf::View(sf::FloatRect(0, 0, screenwidth, screenheight));
	view.setCenter(start, start);
	Game.player.player_sprt.setOrigin( 44.f, 104.f);
	Game.player.position.x = start;
	Game.player.position.y = start;
	std::cout<<"InGameState Seed:" <<MapSeed<<std::endl;
	Game.map.WorldGen(Game.player.position);
};

void InGameState::Pause(){};

void InGameState::Resume(){};

bool InGameState::isPressed(sf::Event event)
{
	return event.type == event.KeyPressed;
};

void InGameState::HandleInput(sf::Event event) 
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
		case sf::Keyboard::R:
			Game.player.position = sf::Vector2f(start, start);
			Game.player.player_sprt.setPosition(Game.player.position);
			view.setCenter(Game.player.position);
			break;
		case sf::Keyboard::C:
			Game.map.WorldGen(Game.player.position);
			break;
	};

	//MouseWheel
	if(event.type == sf::Event::MouseWheelScrolled) {
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
};

void InGameState::Update(StateManager* game, float deltaTime) 
{
	// Calculate movement velocity based on input
	sf::Vector2f velocity(0, 0);
	
	if(Game.player.IsMovingUp) {
		velocity.y -= Game.player.player_speed;
	}
	if(Game.player.IsMovingDown) {
		velocity.y += Game.player.player_speed;
	}
	if(Game.player.IsMovingRight) {
		velocity.x += Game.player.player_speed;
	}
	if(Game.player.IsMovingLeft) {
		velocity.x -= Game.player.player_speed;
	}
	
	// Normalize diagonal movement to prevent faster diagonal speed
	if (velocity.x != 0 && velocity.y != 0) {
		float length = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		velocity.x = (velocity.x / length) * Game.player.player_speed;
		velocity.y = (velocity.y / length) * Game.player.player_speed;
	}
	
	// Apply movement with delta time
	Game.player.position.x += velocity.x * deltaTime;
	Game.player.position.y += velocity.y * deltaTime;
	
	// Update sprite position
	Game.player.player_sprt.setPosition(Game.player.position);
	
	// Update camera to follow player
	view.setCenter(Game.player.position);
	
	// Only generate chunks when player moves significantly (fixes memory leak)
	static sf::Vector2f lastGenPos = Game.player.position;
	float distance = sqrt(pow(Game.player.position.x - lastGenPos.x, 2) + 
						 pow(Game.player.position.y - lastGenPos.y, 2));
	
	if (distance > 6.f) {  // Only when player moves 50 units
		Game.map.WorldGen(Game.player.position);
		lastGenPos = Game.player.position;
	}
	
	// Update animation with delta time
	Game.player.animation.update(deltaTime);
};

void InGameState::Draw(sf::RenderWindow& renderer)
{
	renderer.clear();
	renderer.setView(view);
	
	for(const Chunk& chunk : Game.map.ChunkArr) {
		renderer.draw(chunk);
	}
	
	renderer.draw(Game.player.player_sprt);
	renderer.display();
};
