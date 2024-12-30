#include <ostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>  
#include <SFML/Window.hpp>
#include "Game/Game.hpp"
using namespace std;

int main()
{
    Game game;
    game.Run();
    return 0;
}
