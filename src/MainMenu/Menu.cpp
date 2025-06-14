#include "MainMenu/Menu.hpp"

Menu::Menu() {

	this->menu_texture_idle.loadFromFile("/home/fiveeght/Proc_Gen/src/MainMenu/Menu_Buttons_idle.png");
	this->menu_texture_hover.loadFromFile("/home/fiveeght/Proc_Gen/src/MainMenu/Menu Buttons_pressed.png");
	MenuButtons.resize(BUTTONS_COUNT);

	int ButtonWidth = 600;
	int ButtonHeight = 200;

	int gapx = 9;
	int gapy = 8;

	MenuButtons[NEW_GAME].setTexture(menu_texture_idle);
	MenuButtons[NEW_GAME].setTextureRect(sf::IntRect{0 * (ButtonWidth + gapx), 3 * (ButtonHeight + gapy), ButtonWidth, ButtonHeight});
	MenuButtons[NEW_GAME].setPosition(((view.getSize().x - ButtonWidth) / 1.f), (0 * ((ButtonHeight / 1.4f) + gapy))+ 120);
	MenuButtons[NEW_GAME].setScale(0.4, 0.4);


	MenuButtons[LOAD].setTexture(menu_texture_idle);
	MenuButtons[LOAD].setTextureRect(sf::IntRect{2 * (ButtonWidth + gapx), 0 * (ButtonHeight + gapy), ButtonWidth, ButtonHeight});
	MenuButtons[LOAD].setPosition(((view.getSize().x - ButtonWidth) / 1.f), (1 * ((ButtonHeight / 1.4f) + gapy))+ 120);
	MenuButtons[LOAD].setScale(0.4, 0.4);


	MenuButtons[OPTIONS].setTexture(menu_texture_idle);
	MenuButtons[OPTIONS].setTextureRect(sf::IntRect{2 * (ButtonWidth + gapx), 2 * (ButtonHeight + gapy), ButtonWidth, ButtonHeight});
	MenuButtons[OPTIONS].setPosition(((view.getSize().x - ButtonWidth) / 1.f), (2 * ((ButtonHeight / 1.4f) + gapy))+ 120);
	MenuButtons[OPTIONS].setScale(0.4, 0.4);


	MenuButtons[EXIT].setTexture(menu_texture_idle);
	MenuButtons[EXIT].setTextureRect(sf::IntRect{2 * (ButtonWidth + gapx), 3 * (ButtonHeight + gapy), ButtonWidth, ButtonHeight});
	MenuButtons[EXIT].setPosition(((view.getSize().x - ButtonWidth) / 1.f), (3 * ((ButtonHeight / 1.4f) + gapy))+ 120);
	MenuButtons[EXIT].setScale(0.4, 0.4);

};

void Menu::Pause() {};

void Menu::Resume() {};

void Menu::HandleInput(sf::Event event){};

void Menu::HandleInput(sf::Event event, sf::RenderWindow &render) {

	if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousepos = render.mapPixelToCoords(sf::Mouse::getPosition(render), view);
		if(mousepos.x >= 400 && mousepos.x <= 640 && mousepos.y >= 120 && mousepos.y <= 200) {
			hover_NEW_GAME = true;
		}
		else{
			hover_NEW_GAME = false;
		}


		if(mousepos.x >= 400 && mousepos.x <= 640 && mousepos.y >= 272 && mousepos.y <= 352) {
			hover_LOAD = true;
		}
		else{
			hover_LOAD = false;
		}


		if(mousepos.x >= 400 && mousepos.x <= 640 && mousepos.y >= 422 && mousepos.y <= 502) {
			hover_OPTIONS = true;
		}
		else{
			hover_OPTIONS = false;
		}


		if(mousepos.x >= 400 && mousepos.x <= 640 && mousepos.y >= 572 && mousepos.y <= 654) {
			hover_EXIT = true;
			MenuButtons[EXIT].setTexture(menu_texture_hover);
		}
		else{
			hover_EXIT = false;
			MenuButtons[EXIT].setTexture(menu_texture_idle);
		}


		std::cout<<
		"X: "<<render.mapPixelToCoords(sf::Mouse::getPosition(render), view).x<<"\n"<<
		"Y: "<<render.mapPixelToCoords(sf::Mouse::getPosition(render), view).y<<std::endl;
	};

	if(event.type == sf::Event::MouseButtonPressed) {
		trigger_NEW_GAME = true;
	}

}

void Menu::Update(StateManager *game) {
	if(hover_NEW_GAME) {
		MenuButtons[NEW_GAME].setTexture(menu_texture_hover);
	}
	else {
		MenuButtons[NEW_GAME].setTexture(menu_texture_idle);
	}


	if(hover_LOAD) {
		MenuButtons[LOAD].setTexture(menu_texture_hover);
	}
	else {
		MenuButtons[LOAD].setTexture(menu_texture_idle);
	}


	if(hover_OPTIONS) {
		MenuButtons[OPTIONS].setTexture(menu_texture_hover);
	}
	else {
		MenuButtons[OPTIONS].setTexture(menu_texture_idle);
	}


	if(hover_EXIT) {
		MenuButtons[EXIT].setTexture(menu_texture_hover);
	}
	else {
		MenuButtons[EXIT].setTexture(menu_texture_idle);
	}

	if(trigger_NEW_GAME) {
		trigger_NEW_GAME = false;
		game->AddState(std::make_unique<MapSelectionState>(), true);
		game->ProcessStateChanges();
	}
};

void Menu::Draw(sf::RenderWindow &renderer) {
	renderer.clear();
	renderer.setView(view);
	
	renderer.draw(MenuButtons[NEW_GAME]);
	renderer.draw(MenuButtons[LOAD]);
	renderer.draw(MenuButtons[OPTIONS]);
	renderer.draw(MenuButtons[EXIT]);
	renderer.display();
	
};
