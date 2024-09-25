#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "SFML/Window/Event.hpp"
#include "State/GameState.hpp"
#include "iostream"
#include <algorithm>
#include <stack>
#include <memory>
#include <vector>

typedef std::unique_ptr<GameState> Stateref;
class StateManager
{
public:
    StateManager() {}
    ~StateManager() {}

    void AddState(Stateref newState, bool isReplacing = true) 
    {
        this->IsAdding = true;
        this->isReplacing = isReplacing;

        this->newState = std::move(newState);
    };
    void RemoveState() {
        this->IsRemoving = true;
    };

    void ProcessStateChanges(){
        if(this->IsRemoving && !this->states.empty() )
        {
            this->states.pop();
            
            if ( !this-> states.empty() )
            {
                this->states.top()->Resume();
            }

            this->IsRemoving = false;
        }

        if ( this->IsAdding) 
        {
            if( !this->states.empty()) {

                if( this->isReplacing ) {

                    this->states.pop();
                }
                else {
                    this->states.top()->Pause();
                }
            }
            this->states.push( std::move(this->newState));
            this->states.top()->Init( );
            this->IsAdding = false;
        }
    };

    Stateref &GetActiveState() {
        return this->states.top();
    };

    
private:
    std::stack<Stateref> states;
    Stateref newState;

    bool IsRemoving;
    bool IsAdding;
    bool isReplacing;

};

#endif
