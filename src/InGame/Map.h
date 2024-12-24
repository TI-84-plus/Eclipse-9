#ifndef MAP_H
#define MAP_H

#include <InGame/TileMap.h>
#include <random>
#include "../../libs/FastNoiseLite.h"
class Map
{
private:
    int seed;

public:
    TileMap map;

    Map(int seed):map {seed}
    {
        this->seed = seed;
    }

};

#endif