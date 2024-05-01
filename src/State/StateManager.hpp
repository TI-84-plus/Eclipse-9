#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "iostream"
#include <stack>
#include <memory>

class State;
class StateManager
{
public:
    //Reason iam using smart pointers here is to prevent object slicing
    std::stack<std::unique_ptr<State>> States;
    template <std::derived_from<State> T>
    void CreateState(){
        States.emplace(std::make_unique<T>());
}
};

#endif
