#include "Observable.h"
#include <iostream>

using namespace std;

namespace state
{
    void Observable::registerObserver(Observer* observer)
    {
        observers.push back(observer);
    }

    void Observable::notifyObserver (StateEvent& event, State& state)
    {
        for(auto observer : observers)
        {
            observer -> stateChanged(event, state);
        }
    }
}