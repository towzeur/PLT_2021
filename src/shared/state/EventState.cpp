
namespace state {
  class Event;
}

#include "EventStateId.h"
#include "Event.h"

namespace state {

  /// class EventState - 
  class EventState : public state::Event {
    // Associations
    // Attributes
  public:
    EventStateId eventState;
    // Operations
  public:
    EventState ();
    EventTypeId const getEventType ();
    Event* const clone ();
    // Setters and Getters
  };

};


