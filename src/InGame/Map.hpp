#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Chunk.hpp"
#include <SFML/System/Vector2.hpp>
#include <random>
#include <iostream>
#include <cmath>
#include "../../libs/FastNoiseLite.h"
#include <vector>
#include <algorithm>
#include <array>

class Map
{
private:
    int seed;
    sf::Texture tileset;
    bool PreGenerate = false;
    bool needsGeneration = false; // Track if we need to generate chunks

    static constexpr std::array<std::pair<int,int>, 64> CHUNK_OFFSETS = {{
    {0,0},

    {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1},

    {-2,-2}, {-2,-1}, {-2,0}, {-2,1}, {-2,2}, 
    {-1,-2}, {-1,2}, 
    {0,-2}, {0,2}, 
	{1,-2}, {1,2}, 
	{2,-2}, {2,-1}, {2,0}, {2,1}, {2,2},

    {-3,-3}, {-3,-2}, {-3,-1}, {-3,0}, {-3,1}, {-3,2}, {-3,3},
    {-2,-3}, {-2,3},
    {-1,-3}, {-1,3},
    {0,-3}, {0,3},
    {1,-3}, {1,3},
    {2,-3}, {2,3},
    {3,-3}, {3,-2}, {3,-1}, {3,0}, {3,1}, {3,2}, {3,3},

    {-4,-4}, {-4,-3}, {-4,-2}, {-4,-1}, {-4,0}, {-4,1}, {-4,2}, {-4,3},
    {-3,-4}, {-2,-4}, {-1,-4}, {0,-4}, {1,-4}, {2,-4}, {3,-4}

}};



public:
    float ChunkSize = 16;
    float ChunksLoaded = 32; 
       
    //Loop counters
    int LoadedChunkX = -(ChunksLoaded/2);
    int LoadedChunkY = -(ChunksLoaded/2);
    int ChunkLoadCounter = 0;


    std::vector<Chunk> ChunkArr;
    std::vector<sf::Vector2f> LoadedMap;

    // Public method to check if generation is needed
    bool NeedsGeneration() const { return needsGeneration; }

    Map(int seed)
    {
        this->seed = seed;
        tileset.loadFromFile("assets/tileset.png");
    }
    
    void StartWorldGen(sf::Vector2f player_pos) {
        std::cout<<ChunkLoadCounter<<std::endl;
        
        // Don't restart generation if it's already in progress
        if(needsGeneration) return;
        
        // Calculate which chunk the player is in
        int player_chunk_x = static_cast<int>(floor(player_pos.x / ChunkSize));
        int player_chunk_y = static_cast<int>(floor(player_pos.y / ChunkSize));
        
        PreGenerate = true;
        needsGeneration = true; // Set flag to start generation

        // Initialize to player's chunk position
        LoadedChunkX = player_chunk_x;
        LoadedChunkY = player_chunk_y;
        ChunkLoadCounter = 0;
    }

    bool StepWorldGen() {
        std::cout<< "1"<<std::endl;
        if(!needsGeneration) return false; 
        
        // Check if we've processed all offsets
        if(ChunkLoadCounter >= CHUNK_OFFSETS.size()) {
            PreGenerate = false;
            needsGeneration = false; // Stop generation
            return true; // Generation complete
        }
        
        // Generate one chunk per frame
        int currentChunkX = LoadedChunkX + CHUNK_OFFSETS[ChunkLoadCounter].first;
        int currentChunkY = LoadedChunkY + CHUNK_OFFSETS[ChunkLoadCounter].second;
        
        if(std::find(LoadedMap.begin(), LoadedMap.end(), sf::Vector2f(currentChunkX, currentChunkY)) == LoadedMap.end()) {
            Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
            chunk.ChunkGen(currentChunkX, currentChunkY);
            LoadedMap.push_back(sf::Vector2f(currentChunkX, currentChunkY));
        }
        
        ChunkLoadCounter++;
        return false; // Still generating
    }

    void WorldGen(sf::Vector2f player_pos)  
    {

        


        // for(float LoadedChunkY = player_chunkPosY-(ChunksLoaded/2); LoadedChunkY < ChunksLoaded+(player_chunkPosY-(ChunksLoaded/2)); LoadedChunkY++) 
        // {
        //     for(float LoadedChunkX = player_chunkPosX-(ChunksLoaded/2); LoadedChunkX < ChunksLoaded+(player_chunkPosX-(ChunksLoaded/2)); LoadedChunkX++) 
        //     {
        //         //Will only run once at the beginning
        //         if(LoadedMap.empty()){
        //             //Add CHunk
        //             Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
        //             chunk.ChunkGen(LoadedChunkX, LoadedChunkY);
        //             LoadedMap.push_back(sf::Vector2f(LoadedChunkX, LoadedChunkY));
        //         }
        //         //Check if Map is already Loaded if LoadMap not empty aka not first time running the loops executable
        //         else if(!LoadedMap.empty()){
        //             //Did not find that particular chunk
        //             if(std::find(LoadedMap.begin(), LoadedMap.end(), sf::Vector2f(LoadedChunkX, LoadedChunkY)) == LoadedMap.end()) {
        //                 // BEFORE creating new chunk, remove any chunks outside the bounds using SWAP-AND-POP
        //                 for (int i = 0; i < LoadedMap.size(); i++) {
        //                     float chunkX = LoadedMap[i].x;
        //                     float chunkY = LoadedMap[i].y;
                            
        //                     // Remove if outside the current bounds
        //                     if (chunkX < minX || chunkX > maxX || chunkY < minY || chunkY > maxY) {
        //                         std::cout << "Creating (" << LoadedChunkX << "," << LoadedChunkY
        //                                   << ") - Removing out-of-bounds (" << chunkX << "," << chunkY << ")" << std::endl;
                                
        //                         // SWAP-AND-POP: Move target to end, then remove
        //                         std::swap(ChunkArr[i], ChunkArr.back());
        //                         std::swap(LoadedMap[i], LoadedMap.back());
                                
        //                         // Remove the last elements (which now contain our target)
        //                         ChunkArr.pop_back();
        //                         LoadedMap.pop_back();
                                
        //                         break; // Only remove one per new chunk creation
        //                     }
        //                 }
                        
        //                 //Add Chunk
        //                 Chunk &chunk = ChunkArr.emplace_back(seed, tileset, ChunkSize, ChunksLoaded);
        //                 chunk.ChunkGen(LoadedChunkX, LoadedChunkY);
        //                 LoadedMap.push_back(sf::Vector2f(LoadedChunkX, LoadedChunkY));
        //             }
        //         }
        //     }
        // }

        std::cout << "Total chunks loaded: " << ChunkArr.size() << std::endl;
    }
};

#endif
