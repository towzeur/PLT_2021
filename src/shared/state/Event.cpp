#include "Event.h"

using namespace state;

Event::~Event() {
    
}

EventTypeId const Event::getEventType () {return EVENT_STATE;}

Event* const Event::clone () {}
