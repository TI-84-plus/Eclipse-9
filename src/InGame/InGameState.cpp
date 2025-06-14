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
			std::cout<<Game.player.player_sprt.getPosition().x<<" "<<Game.player.player_sprt.getPosition().y<<std::endl;
			break;
		case sf::Keyboard::Q:
			Game.player.player_speed = 0.05;
			break;
		case sf::Keyboard::C:
			Game.map.WorldGen(Game.player.position);
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


void InGameState::Update(StateManager* game) {

    //Up
    if(Game.player.IsMovingUp)	
    {
        Game.player.position.y -= Game.player.player_speed;	
		Game.player.player_sprt.setPosition(Game.player.position);
		view.setCenter(Game.player.position);
		Game.map.WorldGen(Game.player.position);
    }
    //Down
    if(Game.player.IsMovingDown) 
    {
        Game.player.position.y += Game.player.player_speed;		
		Game.player.player_sprt.setPosition(Game.player.position);
		view.setCenter(Game.player.position);
		Game.map.WorldGen(Game.player.position);
    }
    //Right
    if(Game.player.IsMovingRight) 
    {
        Game.player.position.x += Game.player.player_speed;
		Game.player.player_sprt.setPosition(Game.player.position);
		view.setCenter(Game.player.position);
		Game.map.WorldGen(Game.player.position);
    }
    //Left
    if(Game.player.IsMovingLeft) 
    {
        Game.player.position.x -= Game.player.player_speed;		
		Game.player.player_sprt.setPosition(Game.player.position);
		view.setCenter(Game.player.position);
		Game.map.WorldGen(Game.player.position);
    }

	Game.player.animation.update(0.8);
	
};


void InGameState::Draw(sf::RenderWindow& renderer) 
{
    renderer.clear();
    //renderer.setView(game->GetActiveState()->view);
    renderer.setView(view);

    for(const Chunk& chunk : Game.map.ChunkArr) 
    {
		renderer.draw(chunk);
	}
    
	renderer.draw(Game.player.player_sprt);
    renderer.display();
};
