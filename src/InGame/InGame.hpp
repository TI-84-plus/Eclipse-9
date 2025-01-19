#ifndef INGAME_H
#define INGAME_H
#include <InGame/Map.hpp>	
#include <InGame/Player.hpp>

class InGame 
{
    public:
        Map map;
		Player player;

        //Controls
        bool IsMovingUp = false;
        bool IsMovingDown = false;
        bool IsMovingRight = false;
        bool IsMovingLeft = false;
		int txt_x = 92, start = 8;
		
        float move_speed = 32.f;

        InGame(int seed): map{seed}
        {
            
        }


};


#endif
