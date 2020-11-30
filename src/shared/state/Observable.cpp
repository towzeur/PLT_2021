#include "Observable.h"

using namespace state;

Observable::~Observable() {
    
}

void Observable::registerObserver(Observer* o) { observers.push_back(o); }

void Observable::unregisterObserver(Observer* o) {
    
}

void Observable::unregisterAllObservers() {
    
}

void Observable::notify(const Event& e) {
    
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
