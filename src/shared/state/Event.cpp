#include "EventTypeId.h"

namespace state {

  /// class Event - 
  class Event {
    // Operations
  public:
    virtual ~Event ();
    virtual EventTypeId const getEventType () = 0;
    virtual Event* const clone () = 0;
    // Setters and Getters
  };

};
