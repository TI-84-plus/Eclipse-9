#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "State/GameState.hpp"
#include "State/StateManager.hpp"
#include "InGame.h"
class InGameState: public GameState 
{
    private:
        InGame Game;
        
    public:
        void processInput() 
        {
           
        }
};

#endif