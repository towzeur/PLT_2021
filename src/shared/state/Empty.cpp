
namespace state {
  class Entity;
}

#include "Entity.h"
#include "CellTypeId.h"
#include "Cell.h"

namespace state {

  /// class Empty - 
  class Empty : public state::Entity {
    // Operations
  public:
    Empty ();
    ~Empty ();
    CellTypeId const getTypeId ();
    bool const equals (const Cell& c1);
    Cell* const clone ();
    // Setters and Getters
  };

};

