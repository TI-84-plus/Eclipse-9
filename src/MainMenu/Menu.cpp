#include "MainMenu/Menu.hpp"

Menu::Menu() {

	this->menu_texture.loadFromFile("/home/fiveeght/Proc_Gen/src/MainMenu/Menu_Buttons_idle.png");
	this->menu_sprite.setTexture(this->menu_texture);
	this->menu_sprite.setTextureRect(sf::IntRect(0, 0, 600, 1030));
	this->menu_sprite.setPosition((600/1.6), screenheight/14);
	std::cout<<menu_texture.getSize().x/2<<std::endl;
	this->menu_sprite.scale(0.5, 0.5);
};

void Menu::Pause() {};

void Menu::Resume() {};

void Menu::HandleInput(sf::Event event) {};

void Menu::Update(StateManager *game) {};

void Menu::Draw(sf::RenderWindow &renderer) {
	renderer.clear();
	renderer.setView(view);
	
	renderer.draw(this->menu_sprite);
	renderer.display();
	
};
