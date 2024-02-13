#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <memory>

class State;
class StateManager
{
public:
    //Reason iam using smart pointers here is because one iam smart and 2 it prevents object slicing
    std::stack<std::unique_ptr<State>> States;
    template <std::derived_from<State> T>
    void CreateState(){
        States.emplace(std::make_unique<T>());
}
};

#endif
