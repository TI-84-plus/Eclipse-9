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
		int width = 16;
		int height = 16;
		int tileTextureDimension = 32;
		int tileWorldDimension = 16;
	
	public:
		sf::VertexArray vertexArray;
		static constexpr float ChunkSize = 16.0f;

		TileMap(int seed, sf::Texture& tileset){
		this->seed = seed;
		this->tileset = tileset;
		vertexArray.resize((width * height) * 4);
		vertexArray.setPrimitiveType(sf::Quads);

        seed2 = modifyseed(seed);
        seed3 = modifyseed(seed2);
        seed4 = modifyseed(seed3);
        seed5 = modifyseed(seed4);
	}

	void TilePosition(int TileX, int TileY, int unsigned_x, int unsigned_y, int chunk_x, int chunk_y) 
	{
		Tile tile(TileX, TileY);
		int unsigned_chunkX = chunk_x+(ChunkSize/2.0f);
		int unsigned_chunkY = chunk_y+(ChunkSize/2.0f);
		sf::Vector2f tile_pos = {float(unsigned_x), float(unsigned_y)};
		sf::Vector2f chunk_pos = {float(unsigned_chunkX), float(unsigned_chunkY)};

		vertexArray.append(sf::Vertex((((sf::Vector2f(0.0f, 0.0f) + tile_pos) + (chunk_pos * (ChunkSize*4))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + 2 + (tile.X*2), tileTextureDimension * tile.Y + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(1.0f, 0.0f) + tile_pos) + (chunk_pos * (ChunkSize*4))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension + 2 + (tile.X*2), tileTextureDimension * tile.Y + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(1.0f, 1.0f) + tile_pos) + (chunk_pos * (ChunkSize*4))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension + 2 + (tile.X*2), tileTextureDimension * tile.Y + tileTextureDimension + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(0.0f, 1.0f) + tile_pos) + (chunk_pos * (ChunkSize*4))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + 2 + (tile.X*2), tileTextureDimension * tile.Y + tileTextureDimension + 2 + (tile.Y*2))));

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



		for(int y = -(height*2); y <= height*2; y++) 
		{
			for(int x = -(width*2); x <= width*2; x++) 
			{
				double Map1 = Layout1.GetNoise(float((chunk_x*(width*4))+x),float((chunk_y*(height*4)+y)));
        		double Map2 = Layout2.GetNoise(float((chunk_x*(width*4))+x),float((chunk_y*(height*4)+y)));
        		double Map3 = Layout3.GetNoise(float((chunk_x*(width*4))+x),float((chunk_y*(height*4)+y)));
        		double Map4 = Layout4.GetNoise(float((chunk_x*(width*4))+x),float((chunk_y*(height*4)+y)));
        		double Map5 = Layout5.GetNoise(float((chunk_x*(width*4))+x),float((chunk_y*(height*4)+y)));
        		double Layout = Map1 + Map2 + Map3 + Map4 + Map5;
        		Layout = (Layout + 1.0) / 2.0;
        		Layout = int(Layout * 255);
				float unsigned_y = std::floor((y+(height*2.f)));
				float unsigned_x = std::floor((x+(width*2.f)));
				

                if(chunk_x ==-8 && chunk_y == -8 && y == -32 && x == -32) 
				{
                    std::cout<<"Second: "<<unsigned_x<<std::endl;
				}

				if (Layout < 100)
				{
					TilePosition(4, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
				}

				else if (Layout < 120) 
				{
					TilePosition(3, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
				}

				else
				{
					//Sand
                    if(Layout < 160)
                    {
						TilePosition(2, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
                    }
					//Shallow Forest
                    else if(Layout < 190)
                    {
						TilePosition(0, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
                    }
					//Dense forest
                    else if(Layout < 250) 
                    {
						TilePosition(1, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
                    }
					//Shallow dirt
                    else if(Layout < 285) 
                    {
						TilePosition(5, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
                    }
					//Dense Dirt
                    else if(Layout < 300) 
                    {
						TilePosition(6, 0, unsigned_x, unsigned_y, chunk_x, chunk_y);
                    }
					//Mountains
                    else if(Layout < 320)
                    {
						TilePosition(0, 1, unsigned_x, unsigned_y, chunk_x, chunk_y);
                    }
					//Dense Snow
                    else
                    {

						TilePosition(1, 1, unsigned_x, unsigned_y, chunk_x, chunk_y);
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
