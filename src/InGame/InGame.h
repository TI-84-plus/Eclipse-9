#ifndef INGAME_H
#define INGAME_H
#include <InGame/Map.h>

class InGame 
{
    public:
        Map map;

        //Controls
        bool IsMovingUp = false;
        bool IsMovingDown = false;
        bool IsMovingRight = false;
        bool IsMovingLeft = false;

        int move_speed = 64;

        InGame(int seed): map{seed}
        {
            
        }


};

#endif