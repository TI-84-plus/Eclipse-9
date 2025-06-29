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
class Chunk : public sf::Drawable{
		
	private:
		sf::Texture tileset;
		int seed, seed2, seed3, seed4, seed5;

		int tileTextureDimension = 32;
		double tileWorldDimension = 1;
		float ChunkSize;
		float ChunksLoaded;
		sf::VertexArray lines;
		int currentVertexIndex = 0;
	
	public:
		sf::VertexArray vertexArray;
		sf::Vector2f ChunkPosition;

		Chunk(int seed, sf::Texture& tileset, float ChunkSize, float ChunksLoaded){
		
		this->ChunksLoaded = ChunksLoaded;
		this->ChunkSize = ChunkSize;
		this->seed = seed;
		this->tileset = tileset;
		vertexArray.resize(ChunkSize * ChunkSize * 4);
		vertexArray.setPrimitiveType(sf::Quads);

		lines.resize(ChunksLoaded*ChunksLoaded);
		lines.setPrimitiveType(sf::Lines);

        seed2 = modifyseed(seed);
        seed3 = modifyseed(seed2);
        seed4 = modifyseed(seed3);
        seed5 = modifyseed(seed4);
	}

	
	void TilePosition(int TileX, int TileY, int x, int y, int chunk_x, int chunk_y) 
	{
		// Calculate world position: chunk position * chunk size + tile position within chunk
		float worldX = (chunk_x * ChunkSize) + x;
		float worldY = (chunk_y * ChunkSize) + y;
		
		// Convert to screen coordinates (assuming 1 tile = 1 pixel for now)
		sf::Vector2f screenPos = sf::Vector2f(worldX * tileWorldDimension, worldY * tileWorldDimension);
		
		// Calculate texture coordinates (32x32 tiles with 2px spacing)
		float texX = TileX * (tileTextureDimension + 2) + 2;
		float texY = TileY * (tileTextureDimension + 2) + 2;

		// Set vertex positions (quad corners)
		vertexArray[currentVertexIndex++] = sf::Vertex(
			sf::Vector2f(screenPos.x, screenPos.y), 
			sf::Vector2f(texX, texY)
		);

		vertexArray[currentVertexIndex++] = sf::Vertex(
			sf::Vector2f(screenPos.x + tileWorldDimension, screenPos.y), 
			sf::Vector2f(texX + tileTextureDimension, texY)
		);

		vertexArray[currentVertexIndex++] = sf::Vertex(
			sf::Vector2f(screenPos.x + tileWorldDimension, screenPos.y + tileWorldDimension), 
			sf::Vector2f(texX + tileTextureDimension, texY + tileTextureDimension)
		);

		vertexArray[currentVertexIndex++] = sf::Vertex(
			sf::Vector2f(screenPos.x, screenPos.y + tileWorldDimension), 
			sf::Vector2f(texX, texY + tileTextureDimension)
		);
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
		ChunkPosition.x = chunk_x;
		ChunkPosition.y = chunk_y;
		currentVertexIndex = 0;
        //NoiseMaps
        FastNoiseLite Layout1= noiseparams(4, 0.001, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed);   //Layouts
        FastNoiseLite Layout2= noiseparams(4, 0.002, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed2);
        FastNoiseLite Layout3= noiseparams(4, 0.004, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed3);
        FastNoiseLite Layout4= noiseparams(4, 0.008, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed4);
        FastNoiseLite Layout5= noiseparams(4, 0.0016, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed5);



		for(int y = 0; y < ChunkSize; y++) 
		{
			for(int x = 0; x < ChunkSize; x++) 
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
		target.draw(lines);
		// std::cout<<tileset.getSize().y<<std::endl;
	}
};

#endif
