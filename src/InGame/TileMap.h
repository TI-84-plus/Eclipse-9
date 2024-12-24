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
		int width = 16;
		int height = 16;
		int ChunkSize = 16;
		float tileTextureDimension = 16.f;
		float tileWorldDimension = 32.f;
	
	public:
		TileMap(int seed){
		this->tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
		// this->width = width;
		// this->height = height;
		// this->tileTextureDimension = tileTextureDimension;
		// this->tileWorldDimension = tileWorldDimension;

		vertexArray.resize((width * height) * 4);
		vertexArray.setPrimitiveType(sf::Quads);
		
		Tile tile(1, 0);
		for (int y = 0; y < width; y++) {
			
			for (int x = 0; x < height; x++) {
				
				AddVertices(tile, sf::Vector2f((float)x, (float)y));
			}
		}
		ChunkGen(seed);
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

	void ChunkGen(int seed)
    {
		std::cout<<"ChunkGen: "<<seed<<std::endl;
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


		for(int chunk_x = -(chunkSize/2); chunk_x < chunkSize/2; chunk_x++) 
		{
			for(int chunk_y = -(chunkSize/2); chunk_y < chunkSize/2; chunk_y++) 
			{
				for(int y = -(height*2); y < height*2; y++) 
				{
					for(int x = -(width*2); x < width*2; x++) 
					{
						double Map1 = Layout1.GetNoise(float((chunk_x* (width*4))+x),float((chunk_y* (height*4))+y));
                		double Map2 = Layout2.GetNoise(float((chunk_x* (width*4))+x),float((chunk_y* (height*4))+y));
                		double Map3 = Layout3.GetNoise(float((chunk_x* (width*4))+x),float((chunk_y* (height*4))+y));
                		double Map4 = Layout4.GetNoise(float((chunk_x* (width*4))+x),float((chunk_y* (height*4))+y));
                		double Map5 = Layout5.GetNoise(float((chunk_x* (width*4))+x),float((chunk_y* (height*4))+y));
                		double Layout = Map1 + Map2 + Map3 + Map4 + Map5;

                		Layout = (Layout + 1.0) / 2.0;
                		Layout = int(Layout* 255);
                		int CurrentTileIndex = ((y*width)+x);
						if(chunk_x ==-8 && chunk_y == -8 && y == -32 && x == -32) 
						{
							std::cout<<"Second: "<<Layout<<std::endl;
						}

						if (Layout < 100)
                		{

                		}
					}
				}
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
