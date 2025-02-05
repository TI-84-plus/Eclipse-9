#ifndef MAP_H
#define MAP_H

#include "Chunk.hpp"
#include <random>
#include <iostream>
#include "../../libs/FastNoiseLite.h"

class Map
{
private:
    int seed;
	sf::Texture tileset;

public:
	float ChunkSize = 4;
	float ChunksLoaded = 16;
	
    std::vector<Chunk> ChunkArr;

    Map(int seed)
    {
        this->seed = seed;
		tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
    }

    std::vector<Chunk> WorldGen(sf::Vector2f player_pos)  
    {
		
		float player_chunkPosY = round(player_pos.y/ChunkSize);
		float player_chunkPosX = round(player_pos.x/ChunkSize);
		

        for(float LoadedChunkY = player_chunkPosY-(ChunksLoaded/2); LoadedChunkY < ChunksLoaded+(player_chunkPosY-(ChunksLoaded/2)); LoadedChunkY++) 
        {
			for(float LoadedChunkX = player_chunkPosX-(ChunksLoaded/2); LoadedChunkX < ChunksLoaded+(player_chunkPosX-(ChunksLoaded/2)); LoadedChunkX++) 
            {
					
                Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
                chunk.ChunkGen(LoadedChunkX, LoadedChunkY);

            }
        }


        return ChunkArr;
    }

    

};

#endif
