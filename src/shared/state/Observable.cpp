#include "Observable.h"

using namespace state;

Observable::~Observable() {
    
}

void Observable::registerObserver(Observer* o) { observers.push_back(o); }

void Observable::unregisterObserver(Observer* o) { 
    for(auto Observer : observers){
        if(Observer == o){
            observers.pop_back();
        }
    }
}
void Observable::unregisterAllObservers() {
    observers.clear();
}

void Observable::notify(const Event& e) {
    for(auto Observer : observers){
		Observer->stateChanged(e);
	}
}

void Observable::flush() {
    
}

bool Observable::getEnableNotifications() const {
    
}

void Observable::setEnableNotifications(bool enableNotifications) { this->enableNotifications = enableNotifications; }

bool Observable::getEnableCache() const { return enableCache;}

void Observable::setEnableCache(bool enableCache) { this->enableCache = enableCache; }
