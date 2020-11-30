#include "Observable.h"

using namespace state;

Observable::~Observable() {
    
}

void Observable::registerObserver(Observer* o) { observers.push_back(o); }

void Observable::unregisterObserver(Observer* o) { observers.pop_back();}

void Observable::unregisterAllObservers() {
    for(auto Observer : observers){
		observers.pop_back();
	}
    
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

void Observable::setEnableNotifications(bool enableNotifications) {
    
}

bool Observable::getEnableCache() const {
    
}

void Observable::setEnableCache(bool enableCache) {
    
}
