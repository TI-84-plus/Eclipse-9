#ifndef MAP_H
#define MAP_H

#include "Chunk.hpp"
#include <random>
#include <iostream>
#include "../../libs/FastNoiseLite.h"
#include <bits/stdc++.h>

class Map
{
private:
    int seed;
    sf::Texture tileset;

public:
    float ChunkSize = 16;
    float ChunksLoaded = 12;
    
    std::vector<Chunk> ChunkArr;
    std::vector<sf::Vector2f> LoadedMap;



    Map(int seed)
    {
        this->seed = seed;
        tileset.loadFromFile("assets/tileset.png");
    }

    void WorldGen(sf::Vector2f player_pos)  
    {
        
        float player_chunkPosY = round(player_pos.y/ChunkSize);
        float player_chunkPosX = round(player_pos.x/ChunkSize);
        
        std::cout<<"Player world position: "<<player_pos.x<<std::endl;
        
        float halfChunks = ChunksLoaded / 2;
        
        // Calculate the bounds of what SHOULD be loaded
        float minX = player_chunkPosX - halfChunks;
        float maxX = player_chunkPosX + halfChunks - 1;
        float minY = player_chunkPosY - halfChunks;
        float maxY = player_chunkPosY + halfChunks - 1;

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
                }

                //Check if Map is already Loaded if LoadMap not empty aka not first time running the loops executable
                else if(!LoadedMap.empty()){
                    
                    //Did not find that particular chunk
                    if(std::find(LoadedMap.begin(), LoadedMap.end(), sf::Vector2f(LoadedChunkX, LoadedChunkY)) == LoadedMap.end()) {

						// BEFORE creating new chunk, remove any chunks outside the bounds using SWAP-AND-POP
                        for (int i = 0; i < LoadedMap.size(); i++) {
                            float chunkX = LoadedMap[i].x;
                            float chunkY = LoadedMap[i].y;
                            
                            // Remove if outside the current bounds
                            if (chunkX < minX || chunkX > maxX || chunkY < minY || chunkY > maxY) {
                                std::cout << "Creating (" << LoadedChunkX << "," << LoadedChunkY
                                          << ") - Removing out-of-bounds (" << chunkX << "," << chunkY << ")" << std::endl;
                                
                                // SWAP-AND-POP: Move target to end, then remove
                                std::swap(ChunkArr[i], ChunkArr.back());
                                std::swap(LoadedMap[i], LoadedMap.back());
                                
                                // Remove the last elements (which now contain our target)
                                ChunkArr.pop_back();
                                LoadedMap.pop_back();
                                
                                break; // Only remove one per new chunk creation
                            }
                        }
                        
                        //Add Chunk
                        Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
                        chunk.ChunkGen(LoadedChunkX, LoadedChunkY);
                        LoadedMap.push_back(sf::Vector2f(LoadedChunkX, LoadedChunkY));
                        
                    }
                    

                }
            }
        }

        std::cout << "Total chunks loaded: " << ChunkArr.size() << std::endl;
    }

    

};

#endif
