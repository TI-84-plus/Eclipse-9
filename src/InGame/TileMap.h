#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include <cmath>
#include <sys/types.h>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "Tile.h"
class TileMap : public sf::Drawable{
		
		sf::Texture tileset;
		sf::Sprite sprite;
		sf::VertexArray vertexArray;
		int width;
		int height;
		float tileTextureDimension;
		float tileWorldDimension;
	
	public:
		TileMap(int width, int height, float tileTextureDimension, float tileWorldDimension) 
	{
		std::cout<<"TileMap Constructor"<<std::endl;
		this->tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
		this->width = width;
		this->height = height;
		this->tileTextureDimension = tileTextureDimension;
		this->tileWorldDimension = tileWorldDimension;

		vertexArray.resize((width * height) * 4);
		vertexArray.setPrimitiveType(sf::Quads);
		
		Tile tile(0, 1);

		for (int y = 0; y < width; y++) {
			
			for (int x = 0; x < height; x++) {
				
				AddVertices(tile, sf::Vector2f((float)x, (float)y));
			}
		}


	}

	void AddVertices(Tile tile, sf::Vector2f position) 
	{
			vertexArray.append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + position) * tileWorldDimension,
					sf::Vector2f(tileTextureDimension * tile.X, tileTextureDimension * tile.Y)));	//0, 0	text=0, 16

			vertexArray.append(sf::Vertex((sf::Vector2f(1.0f, 0.0f) + position) * tileWorldDimension, 
					sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension, tileTextureDimension * tile.Y)));

			vertexArray.append(sf::Vertex((sf::Vector2f(1.0f, 1.0f) + position) * tileWorldDimension,
					sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension, tileTextureDimension * tile.Y + tileTextureDimension)));	//1, 1

			vertexArray.append(sf::Vertex((sf::Vector2f(0.0f, 1.0f) + position) * tileWorldDimension,
					sf::Vector2f(tileTextureDimension * tile.X, tileTextureDimension * tile.Y + tileTextureDimension)));	//0, 1
					
	
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.texture = &tileset;
		target.draw(vertexArray, states);
	}
};
