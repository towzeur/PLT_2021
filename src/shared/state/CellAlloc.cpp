namespace state {
  class Cell;
  class ACellAlloc;
}

#include "ACellAlloc.h"

namespace state {

  /// class CellAlloc - 
  template <  class E,   typename ID>
  class CellAlloc : public state::ACellAlloc {
    // Attributes
  protected:
    ID id;
    // Operations
  public:
    CellAlloc (ID id);
    Cell* newInstance ();
    // Setters and Getters
    const ID& getId() const;
    void setId(const ID& id);
  };

};
