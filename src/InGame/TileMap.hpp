#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <sys/types.h>
#include "Tile.hpp"
#include <random>
#include "../../libs/FastNoiseLite.h"
class TileMap : public sf::Drawable{
		
	private:
		sf::Texture tileset;
		int seed, seed2, seed3, seed4, seed5;
		int tileTextureDimension = 32;
		int tileWorldDimension = 4;
	
	public:
		sf::VertexArray vertexArray;
		static constexpr float ChunkSize = 16.0f;

		TileMap(int seed, sf::Texture& tileset){
		this->seed = seed;
		this->tileset = tileset;
		vertexArray.resize((ChunkSize*2 * ChunkSize*2) * 4);
		vertexArray.setPrimitiveType(sf::Quads);

        seed2 = modifyseed(seed);
        seed3 = modifyseed(seed2);
        seed4 = modifyseed(seed3);
        seed5 = modifyseed(seed4);
	}

	void TilePosition(int TileX, int TileY, int x, int y, int chunk_x, int chunk_y) 
	{
		Tile tile(TileX, TileY);
		sf::Vector2f tile_pos = {float(x), float(y)};
		sf::Vector2f chunk_pos = {float(chunk_x), float(chunk_y)};

		vertexArray.append(sf::Vertex((((sf::Vector2f(0.0f, 0.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + 2 + (tile.X*2), tileTextureDimension * tile.Y + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(1.0f, 0.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension + 2 + (tile.X*2), tileTextureDimension * tile.Y + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(1.0f, 1.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension + 2 + (tile.X*2), tileTextureDimension * tile.Y + tileTextureDimension + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(0.0f, 1.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + 2 + (tile.X*2), tileTextureDimension * tile.Y + tileTextureDimension + 2 + (tile.Y*2))));

	}

    int modifyseed(int seed)
    {
        std::mt19937 gen(seed);
        return gen();
    }

    FastNoiseLite noiseparams(int oct, double freq, FastNoiseLite::NoiseType type, int seed)
    {
        FastNoiseLite noise;
        noise.SetSeed(seed);
        noise.SetNoiseType(type);
        noise.SetFractalLacunarity(3.0f);
        noise.SetFractalGain(0.5f);
        noise.SetFrequency(freq);
        noise.SetFractalOctaves(oct);
        noise.SetFractalType(noise.FractalType_FBm);
        return noise;
    };

	void ChunkGen(float chunk_x, float chunk_y)
    {
        //NoiseMaps
        FastNoiseLite Layout1= noiseparams(8, 0.00001, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed);   //Layouts
        FastNoiseLite Layout2= noiseparams(8, 0.00002, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed2);
        FastNoiseLite Layout3= noiseparams(8, 0.00004, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed3);
        FastNoiseLite Layout4= noiseparams(8, 0.00008, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed4);
        FastNoiseLite Layout5= noiseparams(8, 0.000016, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed5);



		for(int y = 0; y <= ChunkSize; y++) 
		{
			for(int x = 0; x <= ChunkSize; x++) 
			{
				double Map1 = Layout1.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map2 = Layout2.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map3 = Layout3.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map4 = Layout4.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map5 = Layout5.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Layout = Map1 + Map2 + Map3 + Map4 + Map5;
        		Layout = (Layout + 1.0) / 2.0;
        		Layout = int(Layout * 255);
				

				if (Layout < 100)
				{
					TilePosition(4, 0, x, y, chunk_x, chunk_y);
				}

				else if (Layout < 120) 
				{
					TilePosition(3, 0, x, y, chunk_x, chunk_y);
				}

				else
				{
					//Sand
                    if(Layout < 160)
                    {
						TilePosition(2, 0, x, y, chunk_x, chunk_y);
                    }
					//Shallow Forest
                    else if(Layout < 190)
                    {
						TilePosition(0, 0, x, y, chunk_x, chunk_y);
                    }
					//Dense forest
                    else if(Layout < 250) 
                    {
						TilePosition(1, 0, x, y, chunk_x, chunk_y);
                    }
					//Shallow dirt
                    else if(Layout < 285) 
                    {
						TilePosition(5, 0, x, y, chunk_x, chunk_y);
                    }
					//Dense Dirt
                    else if(Layout < 300) 
                    {
						TilePosition(6, 0, x, y, chunk_x, chunk_y);
                    }
					//Mountains
                    else if(Layout < 320)
                    {
						TilePosition(0, 1, x, y, chunk_x, chunk_y);
                    }
					//Dense Snow
                    else
                    {

						TilePosition(1, 1, x, y, chunk_x, chunk_y);
                    }
                }
			}
		}

	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.texture = &tileset;
		target.draw(vertexArray, states);
		// std::cout<<tileset.getSize().y<<std::endl;
	}
};

#endif
