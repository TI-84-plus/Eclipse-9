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
    std::vector<Chunk> ChunkArr;

    Map(int seed)
    {
        this->seed = seed;
		tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
        WorldGen();
    }

    std::vector<Chunk> WorldGen()  
    {
        for(int chunk_y = -(Chunk::ChunkSize)/2; chunk_y < Chunk::ChunkSize/2; chunk_y++) 
        {
            for(int chunk_x = -(Chunk::ChunkSize)/2; chunk_x < Chunk::ChunkSize/2; chunk_x++) 
            {
                Chunk &chunk = ChunkArr.emplace_back(seed, tileset);
                chunk.ChunkGen(chunk_x, chunk_y);
            }
        }



        return ChunkArr;
    }

    

};

#endif
