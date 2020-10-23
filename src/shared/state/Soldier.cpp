
namespace state {
  class Cell;
  class Entity;
}

#include "Entity.h"
#include "SoldierTypeId.h"
#include "CellTypeId.h"

namespace state {

  /// class Soldier - 
  class Soldier : public state::Entity {
    // Attributes
  private:
     int PA;
    // Operations
  public:
    Soldier ();
    ~Soldier ();
    CellTypeId const getTypeId ();
    bool const equals (const Cell& c1);
    Cell* const clone ();
    // Setters and Getters
  };

};