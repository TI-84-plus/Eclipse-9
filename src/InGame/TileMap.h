#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include <cmath>
#include <sys/types.h>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "Tile.h"
class TileMap : sf::Drawable
{
	private: 
		sf::Texture tileset;
		sf::VertexArray vertexArray;
		int width;
		int height;
		float tileTextureDimension;
		float tileWorldDimension;
	
	public:
		TileMap(sf::Texture tileset, int width, int height, float tileTextureDimension, float tileWorldDimension) 
	{
		this->tileset = tileset;
		this->width = width;
		this->height = height;
		this->tileTextureDimension = tileTextureDimension;
		this->tileWorldDimension = tileWorldDimension;

		vertexArray.resize((width * height) * 4);
		vertexArray.setPrimitiveType(sf::Quads);
		
		Tile tile(0, 1);

		for (int x = 0; x < width; x++) {
			
			for (int y = 0; y < height; y++) {
				
				AddVertices(tile, sf::Vector2f((float)x, (float)y));
			}
		}
	}

	void AddVertices(Tile tile, sf::Vector2f position) 
	{
			vertexArray.append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + position) * tileWorldDimension,
					sf::Vector2f(tileTextureDimension * tile.X, tileTextureDimension * tile.Y)));	//0, 0

			vertexArray.append(sf::Vertex((sf::Vector2f(1.0f, 0.0f) + position) * tileWorldDimension, 
					sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension, tileTextureDimension * tile.Y)));	//1, 0

			vertexArray.append(sf::Vertex((sf::Vector2f(1.0f, 1.0f) + position) * tileWorldDimension,
					sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension, tileTextureDimension * tile.Y + tileTextureDimension)));	//1, 1

			vertexArray.append(sf::Vertex((sf::Vector2f(0.0f, 1.0f) + position) * tileWorldDimension,
					sf::Vector2f(tileTextureDimension * tile.X, tileTextureDimension * tile.Y + tileTextureDimension)));	//0, 1
					
	}

	void draw (sf::RenderTarget &target, sf::RenderStates states) const override
	{
		
	};
};
