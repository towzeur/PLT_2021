
namespace state {
  class Cell;
}

#include "CellTypeId.h"

namespace state {

  /// class Cell - 
  class Cell {
    // Attributes
  protected:
    int row;
    int col;
    // Operations
  public:
    Cell ();
    ~Cell ();
    virtual CellTypeId const getTypeId () = 0;
    virtual bool const isAccessible () = 0;
    bool const equals (const Cell& cell1);
    Cell* const clone ();
    // Setters and Getters
    int getRow() const;
    void setRow(int row);
    int getCol() const;
    void setCol(int col);
  };

};
