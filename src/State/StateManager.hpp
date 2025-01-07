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

        this->_newState = std::move(newState);
    };
    void RemoveState() {
        this->IsRemoving = true;
    };

    void ProcessStateChanges(){
        if(this->IsRemoving && !this->_states.empty() )
        {
            this->_states.pop();
            
            if ( !this->_states.empty() )
            {
                this->_states.top()->Resume();
            }

            this->IsRemoving = false;
        }

        if ( this->IsAdding) 
        {
            if( !this->_states.empty()) {

                if( this->isReplacing ) {

                    this->_states.pop();
                }
                else {
                    this->_states.top()->Pause();
                }
            }
            this->_states.push( std::move(this->_newState));
            this->IsAdding = false;
        }
    };

    Stateref &GetActiveState() {
        return this->_states.top();
    };

    
private:
    std::stack<Stateref> _states;
    Stateref _newState;

    bool IsRemoving;
    bool IsAdding;
    bool isReplacing;

};

#endif
