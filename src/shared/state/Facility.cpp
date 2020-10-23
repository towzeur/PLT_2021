namespace state {
  class Cell;
  class Entity;
}

#include "Entity.h"
#include "FacilityTypeId.h"
#include "CellTypeId.h"

namespace state {

  /// class Facility - 
  class Facility : public state::Entity {
    // Operations
  public:
    Facility ();
    ~Facility ();
    CellTypeId const getTypeId ();
    bool const equals (const Cell& c1);
    Cell* const clone ();
    // Setters and Getters
  };

};

