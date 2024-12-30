#ifndef TILE_HPP
#define TILE_HPP

class Tile {
	public:
		int X;
		int Y;

		sf::Color color;
		Tile(int X, int Y)
		{
			this->X = X;
			this->Y = Y;
		}	
	
};

#endif
