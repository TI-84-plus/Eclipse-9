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
	float ChunkSize = 32;
	float ChunksLoaded = 16;
	
    std::vector<Chunk> ChunkArr;

    Map(int seed)
    {
        this->seed = seed;
		tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
        WorldGen(ChunkSize, ChunksLoaded);
    }

    std::vector<Chunk> WorldGen(float ChunkSize, float ChunksLoaded)  
    {
        for(int chunk_y = 0; chunk_y < ChunksLoaded; chunk_y++) 
        {
            for(int chunk_x = 0; chunk_x < ChunksLoaded; chunk_x++) 
            {
                Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
                chunk.ChunkGen(chunk_x, chunk_y);
            }
        }



        return ChunkArr;
    }

    

};

#endif
