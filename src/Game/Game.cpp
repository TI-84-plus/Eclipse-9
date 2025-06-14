#include "Game/Game.hpp"


Game::Game() 
{
    render.setVerticalSyncEnabled(false);
	render.setFramerateLimit(240);
    render.setKeyRepeatEnabled(false);
    manager.AddState(std::make_unique<Menu>(), true);
    manager.ProcessStateChanges();
}

void Game::Run()
{
    while(IsRunning) 
    {
        Game::ProcessingInput();
        Game::Update();
        Game::Render();
    }
}
//Process Input
void Game::ProcessingInput()
{
    //start = std::chrono::high_resolution_clock::now();
    sf::Event event;
    while (render.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                IsRunning = false;
                render.close();
                break;
            case sf::Event::Resized:
                {sf::FloatRect visibleArea(event.size.width, event.size.height, event.size.width, event.size.height);
                render.setView(sf::View(visibleArea));
                break;}

			case sf::Event::KeyPressed:
                if(Menu* menuState = dynamic_cast<Menu*>(manager.GetActiveState().get())){
                    menuState->HandleInput(event, render);
                }
                else {
                    manager.GetActiveState()->HandleInput(event);
                }
				break;

            case sf::Event::KeyReleased:
                if(Menu* menuState = dynamic_cast<Menu*>(manager.GetActiveState().get())){
                    menuState->HandleInput(event, render);
                }
                else {
                    manager.GetActiveState()->HandleInput(event);
                }
				break;

			case sf::Event::MouseWheelScrolled:
                if(Menu* menuState = dynamic_cast<Menu*>(manager.GetActiveState().get())){
                    menuState->HandleInput(event, render);
                }
                else {
                    manager.GetActiveState()->HandleInput(event);
                }
				break;

			case sf::Event::MouseMoved:
                if(Menu* menuState = dynamic_cast<Menu*>(manager.GetActiveState().get())){
                    menuState->HandleInput(event, render);
                }
                else {
                    manager.GetActiveState()->HandleInput(event);
                }
				break;

			case sf::Event::MouseButtonPressed:
                if(Menu* menuState = dynamic_cast<Menu*>(manager.GetActiveState().get())){
                    menuState->HandleInput(event, render);
                }
                else {
                    manager.GetActiveState()->HandleInput(event);
                }
				break;
        }
    }
}

//Update
void Game::Update()
{
    manager.GetActiveState()->Update(&manager);
}
//Render
void Game::Render()
{
    manager.GetActiveState()->Draw(render);
    //end = std::chrono::high_resolution_clock::now();
    //fps = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    //std::cout<<fps<<std::endl;
};
