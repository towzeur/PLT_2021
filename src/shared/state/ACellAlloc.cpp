namespace state {
  class Cell;
}

#include "Cell.h"

namespace state {

  /// class ACellAlloc - 
  class ACellAlloc {
    // Associations
    // Operations
  public:
    /// 	
    virtual ~ACellAlloc ();
    virtual Cell* newInstance () = 0;
    // Setters and Getters
  };

};
