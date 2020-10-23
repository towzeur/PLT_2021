#include "PlayerStatus.h"
#include <string>
#include <iostream>

namespace state {

  /// class Player - 
  class Player {
    // Attributes
  private:
    static int instanceCount;
    int uid;
    std::string name;
    bool playing;
    PlayerStatus status;
    // Operations
  public:
    Player ();
    ~Player ();
    Player* const clone ();
    // Setters and Getters
  };

};


