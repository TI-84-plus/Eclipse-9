#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
class Tile {
	public:
		int X;
		int Y;
		// sf::Vector2f world_position;

		// sf::Color color;
		Tile(int X, int Y)
		{
			this->X = X;
			this->Y = Y;
		}	
	
};

#endif
