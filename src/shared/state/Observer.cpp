
namespace state {
  class Event;
}

#include "Event.h"

namespace state {

  /// class Observer - 
  class Observer {
    // Operations
  public:
    void virtual stateChanged (const Event& e);
    // Setters and Getters
  };

};

