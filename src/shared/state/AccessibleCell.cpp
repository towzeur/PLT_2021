namespace state {
  class Entity;
  class Cell;
}

#include "Entity.h"
#include "Cell.h"

namespace state {

  /// class AccessibleCell - 
  class AccessibleCell : public state::Cell {
    // Associations
    // Attributes
  private:
    int playerId;
    int territoryId;
    Entity entity;
    // Operations
  public:
    bool const isAccessible ();
    bool const equals (const Cell& cell1);
    Cell* const clone ();
    // Setters and Getters
  };

};


