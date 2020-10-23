
namespace state {
  class Cell;
  class Entity;
}

#include "Entity.h"
#include "TreeTypeId.h"

namespace state {

  /// class Tree - 
  class Tree : public state::Entity {
    // Operations
  public:
    Tree ();
    ~Tree ();
    CellTypeId const getTypeId ();
    bool const equals (const Cell& c1);
    Cell* const clone ();
    // Setters and Getters
  };

};

