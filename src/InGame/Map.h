#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "TileMap.h"

class Map
{

	private: 
		sf::Texture tileset;

	public:
		Map() 
		{
			TileMap map(tileset, 10, 10, 16, 32);
		}


};

#endif
