#include "Observable.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

void Observable::registerObserver (Observer* obs){ observers.push_back(obs); }

void Observable::notifyUpdating (){
    for(auto Observer : observers){
        Observer->engineUpdating();
    }
}

void Observable::notifyUpdated (){
    for(auto Observer : observers){
        Observer->engineUpdated();
    }
}
