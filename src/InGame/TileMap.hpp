#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <sys/types.h>
#include <vector>
#include "Tile.hpp"
class TileMap : public sf::Drawable{
		
	private:
		sf::Texture tileset;
		sf::Sprite sprite;
		sf::VertexArray vertexArray;

		int seed;
		int width = 16;
		int height = 16;
		float tileTextureDimension = 16.f;
		float tileWorldDimension = 32.f;
	
	public:
		int ChunkSize = 16;

		TileMap(int seed){
		this->seed = seed;
		this->tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
		// this->width = width;
		// this->height = height;
		// this->tileTextureDimension = tileTextureDimension;
		// this->tileWorldDimension = tileWorldDimension;

		vertexArray.resize((width * height) * 4);
		vertexArray.setPrimitiveType(sf::Quads);
	}

	void TilePosition(int TileX, int TileY, int unsigned_x, int unsigned_y, int chunk_x, int chunk_y) 
	{
		Tile tile(TileX, TileY);
		float unsigned_chunkX = float(chunk_x+(chunkSize/2));
		float unsigned_chunkY = float(chunk_y+(chunkSize/2));
		sf::Vector2f tile_pos = {float(unsigned_x), float(unsigned_y)};
		sf::Vector2f chunk_pos = {unsigned_chunkX, unsigned_chunkY};

		vertexArray.append(sf::Vertex(((sf::Vector2f(0.0f, 0.0f) + tile_pos) + (chunk_pos * float((chunkSize*4)))) * tileWorldDimension, sf::Vector2f(tileTextureDimension * tile.X, tileTextureDimension * tile.Y)));;
		vertexArray.append(sf::Vertex(((sf::Vector2f(1.0f, 0.0f) + tile_pos) + (chunk_pos * float((chunkSize*4)))) * tileWorldDimension, sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension, tileTextureDimension * tile.Y)));
		vertexArray.append(sf::Vertex(((sf::Vector2f(1.0f, 1.0f) + tile_pos) + (chunk_pos * float((chunkSize*4)))) * tileWorldDimension, sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension, tileTextureDimension * tile.Y + tileTextureDimension)));
		vertexArray.append(sf::Vertex(((sf::Vector2f(0.0f, 1.0f) + tile_pos) + (chunk_pos * float((chunkSize*4)))) * tileWorldDimension, sf::Vector2f(tileTextureDimension * tile.X, tileTextureDimension * tile.Y + tileTextureDimension)));

		if(unsigned_x == 64 && unsigned_y == 64) 
		{
			std::cout<<"Chunk X: "<<unsigned_x<<std::endl;
		}
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

	void ChunkGen(int chunk_x, int chunk_y)
    {
        int seed2 = modifyseed(seed);
        int seed3 = modifyseed(seed2);
        int seed4 = modifyseed(seed3);
        int seed5 = modifyseed(seed4);
        //NoiseMaps
        FastNoiseLite Layout1= noiseparams(4, 0.001, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed);   //Layouts
        FastNoiseLite Layout2= noiseparams(4, 0.002, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed2);
        FastNoiseLite Layout3= noiseparams(4, 0.004, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed3);
        FastNoiseLite Layout4= noiseparams(4, 0.008, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed4);
        FastNoiseLite Layout5= noiseparams(4, 0.0016, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed5);



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
				int unsigned_y = (y+(height*2));
				int unsigned_x = (x+(width*2));
				

                if(chunk_x ==-8 && chunk_y == -8 && y == -32 && x == -32) 
				{
                    std::cout<<"Second: "<<unsigned_x<<std::endl;
				}

				if (Layout < 100)
        		{
					TilePosition(5, 1, unsigned_x, unsigned_y, chunk_x, chunk_y);
        		}

				else if (Layout < 120) 
				{
					TilePosition(3, 2, unsigned_x, unsigned_y, chunk_x, chunk_y);
				}

				else
				{
					TilePosition(1, 2, unsigned_x, unsigned_y, chunk_x, chunk_y);
				}
			}
		}
    }
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.texture = &tileset;		//The White Square problem is probably not at issue but if it does happen 
		target.draw(vertexArray, states);
	}
};

#endif
