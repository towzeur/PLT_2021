#include <vector>
#include <memory>

namespace state {
  class Cell;
}

#include "Cell.h"

namespace state {

  /// class Board - 
  class Board {
    // Associations
    // Attributes
  private:
    int nCol;
    int nRow;
    std::vector<std::unique_ptr<Cell>> board;
    // Operations
  public:
    Board (){
      

    };


    ~Board (){


    };

    Cell* const get (int r, int c){
      /*
      Cell x =  new Cell();
      return &x;
      */
      return 0;
    };

    void set (int r, int c, Cell* cell){


    };

    void remove (int r, int c){



    };


    Board* const clone (){


      return this;
    };
    // Setters and Getters
  };

};
