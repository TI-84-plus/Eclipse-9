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
	float ChunkSize = 16;
	float ChunksLoaded = 32;
	
    std::vector<Chunk> ChunkArr;
	std::vector<sf::Vector2f> LoadedMap;



    Map(int seed)
    {
        this->seed = seed;
		tileset.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
    }

    void WorldGen(sf::Vector2f player_pos)  
    {
		
		float player_chunkPosY = round(player_pos.y/ChunkSize);
		float player_chunkPosX = round(player_pos.x/ChunkSize);
		

        for(float LoadedChunkY = player_chunkPosY-(ChunksLoaded/2); LoadedChunkY < ChunksLoaded+(player_chunkPosY-(ChunksLoaded/2)); LoadedChunkY++) 
        {
			for(float LoadedChunkX = player_chunkPosX-(ChunksLoaded/2); LoadedChunkX < ChunksLoaded+(player_chunkPosX-(ChunksLoaded/2)); LoadedChunkX++) 
            {
				//Will only run once at the beginning
				if(LoadedMap.empty()){

					//Add CHunk
					Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
					chunk.ChunkGen(LoadedChunkX, LoadedChunkY);
					LoadedMap.push_back(sf::Vector2f(LoadedChunkX, LoadedChunkY));
					std::cout<<"First Chunk Added"<<std::endl;
				}

				//Check if Map is already Loaded if LoadMap not empty aka not first time running the loops executable
				else if(!LoadedMap.empty()){
					
					//Did not find that particular chunk
					if(std::find(LoadedMap.begin(), LoadedMap.end(), sf::Vector2f(LoadedChunkX, LoadedChunkY)) == LoadedMap.end()) {
						
						//Add Chunk
						Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
						chunk.ChunkGen(LoadedChunkX, LoadedChunkY);
						LoadedMap.push_back(sf::Vector2f(LoadedChunkX, LoadedChunkY));
						std::cout<<"New Chunk Added"<<std::endl;
					}
					

				}

            }
        }

    }

    

};

#endif
