#include <map>

namespace state {
  class ACellAlloc;
  class CellFactory;
}

#include "ACellAlloc.h"

namespace state {

  /// class CellFactory - 
  class CellFactory {
    // Associations
    // Attributes
  protected:
    std::map<char,ACellAlloc*> list;
    // Operations
  public:
    ~CellFactory ();
    Cell* const newInstance (char id);
    void registerType (char id, ACellAlloc* cell);
    CellFactory* createDefault ();
    // Setters and Getters
    const std::map<char,ACellAlloc*>& getList() const;
    void setList(const std::map<char,ACellAlloc*>& list);
  };

};
