#ifndef INGAME_H
#define INGAME_H
#include <InGame/Map.h>

class InGame 
{
    public:
        Map map;

        InGame(int seed): map{seed}
        {
        }


};

#endif