#ifndef INGAME_H
#define INGAME_H
#include <InGame/TileMap.h>

class InGame 
{
    public:
        TileMap map{10, 10, 16.f, 32.f};

        InGame()
        {
            std::cout<<"InGame created"<<std::endl;
        }
    
};

#endif