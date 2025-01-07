#ifndef MAP_H
#define MAP_H

#include "TileMap.hpp"
#include <random>
#include <iostream>
#include "../../libs/FastNoiseLite.h"

class Map
{
private:
    int seed;

public:
    std::vector<TileMap> ChunkArr;
    Map(int seed)
    {
        this->seed = seed;
        WorldGen();
    }

    std::vector<TileMap> WorldGen()  
    {
        for(int chunk_y = -(TileMap::ChunkSize/2); chunk_y < (TileMap::ChunkSize / 2); chunk_y++) 
        {
            for(int chunk_x = -(TileMap::ChunkSize/2); chunk_x < (TileMap::ChunkSize / 2); chunk_x++) 
            {
                TileMap &chunk = ChunkArr.emplace_back(seed);
                chunk.ChunkGen(chunk_x, chunk_y);
            }
        }



        return ChunkArr;
    }

    

};

#endif
