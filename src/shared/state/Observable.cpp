#include <vector>
#include <memory>

namespace state {
  class Observer;
  class Event;
}

#include "Observer.h"

namespace state {

  /// class Observable - 
  class Observable {
    // Associations
    // Attributes
  private:
    mutable std::vector <Observer*> observers;
     mutable std::vector<std::unique_ptr<Event>> cache;
  protected:
    bool enableNotifications     = true;
    bool enableCache     = false;
    // Operations
  public:
    ~Observable ();
    void registerObserver (Observer* o);
    void unregisterObserver (Observer* o);
    void unregisterAllObservers ();
    void notify (const Event& e);
    void flush ();
    // Setters and Getters
    bool getEnableNotifications() const;
    void setEnableNotifications(bool enableNotifications);
    bool getEnableCache() const;
    void setEnableCache(bool enableCache);
  };

};
