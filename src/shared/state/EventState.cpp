#include "EventState.h"

using namespace state;

EventState::EventState() {
    
}

EventTypeId const EventState::getEventType() { return EVENT_STATE; }

Event* const EventState::clone() {
    EventState* objett = new EventState;
    objett->eventState = this->eventState;
    return objett;
}
