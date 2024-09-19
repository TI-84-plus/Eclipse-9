#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "State/State.hpp"
#include "State/StateManager.hpp"
#include "InGame.h"
class InGameState: public State 
{
    private:
        InGame Game;
        
    public:
        void processInput() 
        {
           
        }
};

#endif