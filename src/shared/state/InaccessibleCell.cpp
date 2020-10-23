
namespace state {
  class Cell;
}

#include "Cell.h"
#include "InaccessibleCellTypeId.h"

namespace state {

  /// class InaccessibleCell - 
  class InaccessibleCell : public state::Cell {
    // Operations
  public:
    bool const isAccessible ();
    CellTypeId const getTypeId ();
    bool const equals (const Cell& cell1);
    Cell* const clone ();
    // Setters and Getters
  };

};
