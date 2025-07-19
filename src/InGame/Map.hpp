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
#include <unordered_set>
#include <memory>

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
    float ChunkSize = 32;
    float ChunksLoaded = 8; 
       
    //Loop counters
    int LoadedChunkX = -(ChunksLoaded/2);
    int LoadedChunkY = -(ChunksLoaded/2);
    int ChunkLoadCounter = 0;


    std::vector<std::unique_ptr<Chunk>> ChunkArr;
    std::unordered_set<int64_t> LoadedMap;
    
    int64_t packBit(int x, int y){
        // std::cout<<"X: "<<static_cast<int64_t>(x) << 32 <<" Y: "<< static_cast<int32_t>(y)<<std::endl;
        // uint32_t xO = static_cast<int32_t>(x + offset)
        // uint32_t yO = static_cast<uin>

        return (static_cast<int64_t>(x) << 32) | static_cast<uint32_t>(y);
        
    };
    
    std::pair<int, int> unpackBit(int64_t packed){
        int x = static_cast<int>(packed >> 32);
        int y = static_cast<int>(packed & 0xFFFFFFFF);
        return std::make_pair(x, y);
    };
    

    // Public method to check if generation is needed
    bool NeedsGeneration() const { return needsGeneration; }

    Map(int seed)
    {
        this->seed = seed;
        tileset.loadFromFile("Assets/Tileset.png");
    }
    
    void StartWorldGen(sf::Vector2f player_pos) {
        
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
        
        if(!LoadedMap.count(packBit(currentChunkX, currentChunkY))) {
            ChunkArr.emplace_back(std::make_unique<Chunk>(seed, tileset, ChunkSize, ChunksLoaded));
            ChunkArr.back()->ChunkGen(currentChunkX, currentChunkY);
            LoadedMap.insert(packBit(currentChunkX, currentChunkY));
        }
        
        ChunkLoadCounter++;
        return false; // Still generating
    }
    
    void removeChunk(int x, int y) {
        int64_t packedCoord = packBit(x, y);
        
        if(LoadedMap.count(packedCoord)) {
            LoadedMap.erase(packedCoord);
            
            // Find chunk in vector and remove using swap and pop
            for(size_t i = 0; i < ChunkArr.size(); ++i) {
                if(ChunkArr[i]->GetChunkX() == x && ChunkArr[i]->GetChunkY() == y) {
                    // Swap with last element and pop
                    if(i != ChunkArr.size() - 1) {
                        std::swap(ChunkArr[i], ChunkArr.back());
                    }
                    ChunkArr.pop_back();
                    break;
                }
            }
        }
    }

};

#endif
