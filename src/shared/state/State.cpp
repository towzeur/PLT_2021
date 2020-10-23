#include <vector>

namespace state {
  class Board;
  class Territory;
  class Player;
  class State;
  class Observable;
}

#include "Board.h"
#include "Territory.h"
#include "Player.h"
#include "Observable.h"

namespace state {

  /// class State - 
  class State : public state::Observable {
    // Associations
    state::Territory *;
    // Attributes
  private:
    bool gameOver;
    unsigned int turn;
    int currentPlayerId;
    int nbPlayers;
    Board board;
    std::vector<Territory> territories;
    std::vector<Player> players;
    // Operations
  public:
    State ();
    State (const State& state1);
    ~State ();
    operator= (const State& state1);
    State* const clone ();
    void setEnableCache (bool newEnableCache );
    void setEnableNotifications (bool newEnableNotifications);
    void flush ();
    // Setters and Getters
    const Territory& get*() const{
      
    };
    void set(const Territory& *);
  };

};
