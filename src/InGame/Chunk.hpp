#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <sys/types.h>
#include "Tile.hpp"
#include <random>
#include <vector>
#include "../../libs/FastNoiseLite.h"
class Chunk : public sf::Drawable{
		
	private:
		sf::Texture *tileset;
		int seed, seed2, seed3, seed4, seed5;

		int tileTextureDimension = 64;
		double tileWorldDimension = 1;
		float ChunkSize;
		float ChunksLoaded;
		sf::VertexArray lines;
		int currentVertexIndex = 0;
		std::vector<std::vector<int>> TileTypes;
		std::vector<std::vector<uint8_t>> Bitmask;
		std::vector<std::vector<bool>> BaseMask;
		// TileVariation vector removed, not needed
	
	public:
		sf::VertexArray vertexArray;
		sf::Vector2f ChunkPosition;

		Chunk(int seed, sf::Texture& tileset, float ChunkSize, float ChunksLoaded){
		
		this->ChunksLoaded = ChunksLoaded;
		this->ChunkSize = ChunkSize;
		this->seed = seed;
		this->tileset = &tileset;
		vertexArray.resize(ChunkSize * ChunkSize * 8);
		vertexArray.setPrimitiveType(sf::Quads);

		lines.resize(ChunksLoaded*ChunksLoaded);
		lines.setPrimitiveType(sf::Lines);

        seed2 = modifyseed(seed);
        seed3 = modifyseed(seed2);
        seed4 = modifyseed(seed3);
        seed5 = modifyseed(seed4);
	}


	int getPriority(int tileType) {
    	switch (tileType) {
        	case 0: return 0; // Deep water
        	case 1: return 1; // Shallow water
        	case 2: return 2; // Sand
        	case 3: return 3; // Grass
        	case 4: return 4; // Dense forest
        	case 5: return 5; // Shallow dirt
        	case 6: return 6; // Dense dirt
        	case 7: return 7; // Mountains
        	case 8: return 8; // Dense snow
        	default: return -1; // Unknown type
    	}
	}


	
	void TilePosition(int TileType, int x, int y, int chunk_x, int chunk_y) 
	{
		int TileCordStart = (TileType*512);
		int TileCordEnd = (TileCordStart+512);
			
		uint8_t mask = Bitmask[y][x];
		int tileCol = rand() % 8;
		int tileRow = 0;

		if ((mask & 0b11111111) == 0b11111111) {
			tileRow = 0; // Full surround
		}
		else if ((mask & 0b00000101) == 0b00000101) {
			tileRow = 0; // Up + Down
		}
		else if ((mask & 0b00001010) == 0b00001010) {
			tileRow = 0; // Left + Right
		}
		else if ((mask & 0b00000011) == 0b00000011) {	
			tileRow = 1; // Up + Right
		}
		else if ((mask & 0b00000110) == 0b00000110) {
			tileRow = 2; // Right + Down
		}
		else if ((mask & 0b00001100) == 0b00001100) {
			tileRow = 3; // Down + Left
		}
		else if ((mask & 0b00001001) == 0b00001001) {
			tileRow = 4; // Up + Left
		}
		else if (mask == 0b00000001) {
			tileRow = 9; // Up only
		}
		else if (mask == 0b00000010) {
			tileRow = 10; // Right only
		}
		else if (mask == 0b00000100) {
			tileRow = 11; // Down only
		}
		else if (mask == 0b00001000) {
			tileRow = 12; // Left only
		}
		else if ((mask & 0b01111111) == 0b01111111) {
    		tileRow = 2; //Top Left
		}
		else if ((mask & 0b11101111) == 0b11101111) {
			tileRow = 3; // Top right
		}
		else if ((mask & 0b11011111) == 0b11011111) {
			tileRow = 4; //Down right
		}
		else if ((mask & 0b10111111) == 0b10111111) {
			tileRow = 1; //Down left
		}
		else {
			tileRow = 0; // Fallback
		}

		//Right + top right and rest are remaining

		BaseMask[y][x] = 0;

		//Up
    	if (y > 0 && !(mask & 1)) {
			int upType = TileTypes[y-1][x];
			if (getPriority(upType) > getPriority(TileType)) {
				BaseMask[y][x] = 1	;
			}
    	}

		//Right
		if (x < ChunkSize-1 && !(mask & 2)) {
    		int rightType = TileTypes[y][x+1];
			if (getPriority(rightType) > getPriority(TileType)) {
				BaseMask[y][x] = 1; // right
			}
		}

		//Bottom
		if (y < ChunkSize-1 && !(mask & 4)) {
			int BottomType = TileTypes[y+1][x];
			if (getPriority(BottomType) > getPriority(TileType)) {
				BaseMask[y][x] = 1;
			}
		}
		
		//Left
		if (x > 0 && !(mask & 8)) {
			int leftType = TileTypes[y][x-1];
			if (getPriority(leftType) > getPriority(TileType)) {
				BaseMask[y][x] = 1;
			}
		}

		// Up-Right
		if (y > 0 && x < ChunkSize-1 && TileTypes[y-1][x+1] != TileType) {
			int upRightType = TileTypes[y-1][x+1];
			if (getPriority(upRightType) > getPriority(TileType)) {
				BaseMask[y][x] = 1;
			}
		}

		// Down-Right
		if (y < ChunkSize-1 && x < ChunkSize-1 && TileTypes[y+1][x+1] != TileType) {
			int downRightType = TileTypes[y+1][x+1];
			if (getPriority(downRightType) > getPriority(TileType)) {
				BaseMask[y][x] = 1;
			}
		}

		// Down-Left
		if (y < ChunkSize-1 && x > 0 && TileTypes[y+1][x-1] != TileType) {
			int downLeftType = TileTypes[y+1][x-1];
			if (getPriority(downLeftType) > getPriority(TileType)) {
				BaseMask[y][x] = 1;
			}
		}
		
		// Up-Left
		if (y > 0 && x > 0 && TileTypes[y-1][x-1] != TileType) {
   			int upLeftType = TileTypes[y-1][x-1];
    		if (getPriority(upLeftType) > getPriority(TileType)) {
				BaseMask[y][x] = 1;
			}
		}
		

		float texX = TileCordStart + (tileCol * 64);
		float texY = tileRow * 64;

		// Calculate world position: chunk position * chunk size + tile position within chunk
		float worldX = (chunk_x * ChunkSize) + x;
		float worldY = (chunk_y * ChunkSize) + y;
		
		// Convert to screen coordinates (assuming 1 tile = 1 pixel for now)
		sf::Vector2f screenPos = sf::Vector2f(worldX * tileWorldDimension, worldY * tileWorldDimension);


		if(BaseMask[y][x]) {
			int baseType = TileType+1;
			int baseTileCordStart = (baseType*512);
			int baseTileCordEnd = (baseTileCordStart+512);
			int baseTileCol = tileCol;
			int baseTileRow = 0;

			float baseTexX = baseTileCordStart + (baseTileCol * 64);
			float baseTexY = baseTileRow * 64;

			vertexArray[currentVertexIndex++] = sf::Vertex(
				sf::Vector2f(screenPos.x, screenPos.y), 
				sf::Vector2f(baseTexX, baseTexY)
			);
			vertexArray[currentVertexIndex++] = sf::Vertex(
        		sf::Vector2f(screenPos.x + tileWorldDimension, screenPos.y), 
        		sf::Vector2f(baseTexX + tileTextureDimension, baseTexY)
    		);
    		vertexArray[currentVertexIndex++] = sf::Vertex(
        		sf::Vector2f(screenPos.x + tileWorldDimension, screenPos.y + tileWorldDimension), 
        		sf::Vector2f(baseTexX + tileTextureDimension, baseTexY + tileTextureDimension)
    		);
    		vertexArray[currentVertexIndex++] = sf::Vertex(
        		sf::Vector2f(screenPos.x, screenPos.y + tileWorldDimension), 
        		sf::Vector2f(baseTexX, baseTexY + tileTextureDimension)
    		);
		}

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
		TileTypes.resize(ChunkSize, std::vector<int>(ChunkSize));
		Bitmask.resize(ChunkSize, std::vector<uint8_t>(ChunkSize, 0));
		BaseMask.resize(ChunkSize, std::vector<bool>(ChunkSize, false));
		// TileVariation vector removed
		
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
					TileTypes[y][x] = 0; //Deep water
				}

				else if (Layout < 120) 
				{
					TileTypes[y][x] = 1; //Shallow water
				}

				//Rest
				else
				{
                    if(Layout < 160)
                    {
						TileTypes[y][x] = 2; //Sand
                    }

                    else if(Layout < 190)
                    {
						TileTypes[y][x] = 3; //Grass	
                    }

					//Dense forest
                    else if(Layout < 250) 
                    {
						TileTypes[y][x] = 4; //Dense forest
                    }
					//Shallow dirt
                    else if(Layout < 285) 
                    {
						// TilePosition(5, x, y, chunk_x, chunk_y);
						TileTypes[y][x] = 5;
                    }
					//Dense Dirt
                    else if(Layout < 300) 
                    {
						// TilePosition(6, x, y, chunk_x, chunk_y);
						TileTypes[y][x] = 6;
                    }
					//Mountains
                    else if(Layout < 320)
                    {
						// TilePosition(7, x, y, chunk_x, chunk_y);
						TileTypes[y][x] = 7;
                    }
					//Dense Snow
                    else
                    {

						// TilePosition(8, x, y, chunk_x, chunk_y);
						TileTypes[y][x] = 8;
                    }
                }
			}
		}


		for (int y = 0; y < ChunkSize; y++) {
			for (int x = 0; x < ChunkSize; x++) {
				uint8_t center = TileTypes[y][x];
				uint8_t mask = 0;
				// Up
				if (y > 0 && TileTypes[y-1][x] == center) mask = mask |= 1;
				// Right
				if (x < ChunkSize-1 && TileTypes[y][x+1] == center) mask = mask |= 2;
				// Down
				if (y < ChunkSize-1 && TileTypes[y+1][x] == center) mask = mask|= 4;
				// Left
				if (x > 0 && TileTypes[y][x-1] == center) mask = mask|= 8;
				// Top right
				if (y > 0 && x < ChunkSize-1 && TileTypes[y-1][x+1] == center) mask |= 16;
				// Down right
				if (y < ChunkSize-1 && x < ChunkSize-1 && TileTypes[y+1][x+1] == center) mask |= 32;
				// Down left
				if (y < ChunkSize-1 && x > 0 && TileTypes[y+1][x-1] == center) mask |= 64;
				// Top left
				if (y > 0 && x > 0 && TileTypes[y-1][x-1] == center) mask |= 128;

				Bitmask[y][x] = mask;
			}
		}
		
		for(int y = 0; y < ChunkSize; y++) {
    		for(int x = 0; x < ChunkSize; x++) {
        		TilePosition(TileTypes[y][x], x, y, chunk_x, chunk_y);
  	  		}
		}
	}


	
	int GetChunkX() const { return static_cast<int>(ChunkPosition.x); }
	int GetChunkY() const { return static_cast<int>(ChunkPosition.y); }
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.texture = this->tileset;
		target.draw(vertexArray, states);
		target.draw(lines);
		// std::cout<<tileset.getSize().y<<std::endl;
	}
};

#endif
