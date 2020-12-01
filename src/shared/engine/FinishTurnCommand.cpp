#include "FinishTurnCommand.h"
<<<<<<< HEAD
#include <iostream>


using namespace engine;
using namespace state;
using namespace std;


FinishTurnCommand::FinishTurnCommand (){ commandTypeId=FINISH_TURN; }

Json::Value FinishTurnCommand::serialize (){
    Json::Value newCommand;
    return newCommand["commandTypeId"]= commandTypeId;
}

=======
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

FinishTurnCommand::FinishTurnCommand() { this->commandTypeId = FINISH_TURN; }

void FinishTurnCommand::execute(state::State &state) {

  std::vector<std::unique_ptr<state::Cell>> &cells =
      state.getBoard().getCells();
  for (std::unique_ptr<state::Cell> &soldier : cells) {
    if (soldier->getEntity().isSoldier()) {
      state::Soldier &s = dynamic_cast<state::Soldier &>(soldier->getEntity());
      // Reset PA of all soldiers at the end of the turn
      if (s.getPA() == 0) {
        s.setPA(0);
      }
    }
  }

  std::vector<state::Territory> &territories = currentPlayer.getTerritories();

  for (state::Territory &territory : territories) {
    // Reset selected
    territory.setSelected(false);
  }

  state.setTurn(state.getTurn() + 1);
}

Json::Value FinishTurnCommand::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;

  return newCommand;
}
>>>>>>> 895345dc02f72c8b1ffbd22bd8f1f95535357026
