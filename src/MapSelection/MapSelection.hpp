#ifndef MENUMAP_H
#define MENUMAP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include "S_Chunk.hpp"
#include "../../libs/FastNoiseLite.h"

const int screenwidth = 1920;
const int screenheight = 1080;
class MapSelection
{
private:
    int x_counter = ((-chunkSize/2)-1);
    int y_counter = -(chunkSize/2);

public:
    int seed;
    bool NoBoundry = false;
    int mov_speed = 16;
    int MSScale = 2.f;
    bool MapGenerationRequested = false;
    bool selected = false;
    bool isopen = true;

    //Controls
    bool IsMovingUp = false;
    bool IsMovingDown = false;
    bool IsMovingRight = false;
    bool IsMovingLeft = false;

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


    std::vector<S_Chunk> WorldGen()
    {

		std::vector<S_Chunk> chunks;
        std::random_device rd;
        std::mt19937 gen(rd());
        seed = gen();
        std::cout<<"Constructor called, value is: "<<seed<<std::endl;

        while (x_counter != (chunkSize/2) || y_counter != (chunkSize/2))
        {
            x_counter++;
            
            if(x_counter == ((chunkSize/2)))
            {
                x_counter = -(chunkSize/2);
                y_counter++;
                if(y_counter == ((chunkSize/2)))
                {
                    MapGenerationRequested = false;
                    x_counter = ((-chunkSize/2)-1);
                    y_counter = -(chunkSize/2);
                    break;
                }
            }
            S_Chunk &chunk = chunks.emplace_back(); //2.
            chunk = ChunkGen(seed, x_counter, y_counter); 
        }
        std::cout<<"Chunk returned"<<std::endl;
        return chunks;
    }


    S_Chunk ChunkGen(int seed, float chunk_x, float chunk_y) //1. Move this function defination to Chunk constructor
    {   
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
        S_Chunk chunk;
        // pixel_Y
        for (int y = -screen_height / 2; y < screen_height / 2; ++y)
        {
            // pixel_X
            for (int x = -screen_width / 2; x < screen_width / 2; ++x)
            {
                double Map1 = Layout1.GetNoise(float((chunk_x * screen_width)+x),float((chunk_y * screen_height)+y));
                double Map2 = Layout2.GetNoise(float((chunk_x * screen_width)+x),float((chunk_y * screen_height)+y));
                double Map3 = Layout3.GetNoise(float((chunk_x * screen_width)+x),float((chunk_y * screen_height)+y));
                double Map4 = Layout4.GetNoise(float((chunk_x * screen_width)+x),float((chunk_y * screen_height)+y));
                double Map5 = Layout5.GetNoise(float((chunk_x * screen_width)+x),float((chunk_y * screen_height)+y));
                double Layout = Map1 + Map2 + Map3 + Map4 + Map5;

                Layout = (Layout + 1.0) / 2.0;
                Layout = int(Layout* 255);
                int unsigned_y = y + ((screen_width / 2));
                int unsigned_x = x + ((screen_height / 2));
                int CurrentPixelIndex2 = ((unsigned_y * screen_width) + unsigned_x) * 4;

                if(chunk_x ==-8 && chunk_y == -8 && y == -32 && x == -32) 
				{
                    std::cout<<"First: "<<(float((chunk_x * screen_width)+x))<<std::endl;
				}

                //Deep level water
                if (Layout < 100)
                {
                    chunk.pixels[CurrentPixelIndex2] = {214}; //55
                    chunk.pixels[CurrentPixelIndex2 + 1] = {212}; //102 
                    chunk.pixels[CurrentPixelIndex2 + 2] = {209}; //200
                    chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                }
                // Shallow water
                else if (Layout < 120  )
                {
                    chunk.pixels[CurrentPixelIndex2] = {168}; //55
                    chunk.pixels[CurrentPixelIndex2 + 1] = {166}; //102 
                    chunk.pixels[CurrentPixelIndex2 + 2] = {163}; //200
                    chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                }
                // Rest
                else
                {
					//Sand
                    if(Layout < 160)
                    {
                        chunk.pixels[CurrentPixelIndex2] = {123};
                        chunk.pixels[CurrentPixelIndex2 + 1] = {121};
                        chunk.pixels[CurrentPixelIndex2 + 2] = {117};
                        chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                    }
					//Shallow Forest
                    else if(Layout < 190)
                    {
                        chunk.pixels[CurrentPixelIndex2] = {54}; //55
                        chunk.pixels[CurrentPixelIndex2 + 1] = {56}; //102
                        chunk.pixels[CurrentPixelIndex2 + 2] = {58}; //200
                        chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                    }
					//Dense forest
                    else if(Layout < 250) 
                    {
                        chunk.pixels[CurrentPixelIndex2] = {58}; //55
                        chunk.pixels[CurrentPixelIndex2 + 1] = {57}; //102
                        chunk.pixels[CurrentPixelIndex2 + 2] = {54}; //200
                        chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                    }
					//Shallow dirt
                    else if(Layout < 285) 
                    {
                        chunk.pixels[CurrentPixelIndex2] = {99}; //55
                        chunk.pixels[CurrentPixelIndex2 + 1] = {70}; //102
                        chunk.pixels[CurrentPixelIndex2 + 2] = {52}; //200
                        chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                    }
					//Dense Dirt
                    else if(Layout < 300) 
                    {
                        chunk.pixels[CurrentPixelIndex2] = {76}; //55
                        chunk.pixels[CurrentPixelIndex2 + 1] = {48}; //102
                        chunk.pixels[CurrentPixelIndex2 + 2] = {27}; //200
                        chunk.pixels[CurrentPixelIndex2 + 3] = {255};
                    }
					//Light snow
                    else if(Layout < 320)
                    {
                        chunk.pixels[CurrentPixelIndex2] = {211}; //55
                        chunk.pixels[CurrentPixelIndex2 + 1] = {211}; //102
                        chunk.pixels[CurrentPixelIndex2 + 2] = {211}; //200
                        chunk.pixels[CurrentPixelIndex2 + 3] = {211};
                    }
					//Dense Snow
                    else
                    {

                        chunk.pixels[CurrentPixelIndex2] = {255}; //55
                        chunk.pixels[CurrentPixelIndex2 + 1] = {255}; //102
                        chunk.pixels[CurrentPixelIndex2 + 2] = {255}; //200
                        chunk.pixels[CurrentPixelIndex2 + 3] = {255}; 
                    }
                }
            }
        }

        chunk.chunk_position.x = chunk_x;
        chunk.chunk_position.y = chunk_y;
        chunk.sprite.setPosition(screen_width * (chunk_x) * MSScale, screen_height * (chunk_y) * MSScale);
        chunk.sprite.setTexture(*chunk.texture);
        chunk.texture->update(chunk.pixels.data());
        chunk.sprite.setScale(MSScale, MSScale);
        return chunk;
    }
};
#endif
