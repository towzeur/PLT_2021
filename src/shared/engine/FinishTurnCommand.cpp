#include <iostream>
#include <unistd.h>

#include "FinishTurnCommand.h"
//#include "engine.h"
#include "state/AccessibleCell.h"

using namespace engine;

FinishTurnCommand::FinishTurnCommand() { this->commandTypeId = FINISH_TURN; }

void FinishTurnCommand::execute(state::State &state) {

  std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();

  for (std::shared_ptr<state::Cell> &c : cells) {
    if (c->isAccessible()) {
      state::AccessibleCell *ac = (state::AccessibleCell *)c.get();
      if (ac->getEntity().isSoldier()) {
        // Reset PA of all soldiers at the end of the turn
        ac->getEntity().setActionPoint(1);
      }
    }
  }

  std::vector<std::shared_ptr<state::Territory>> territories =
      currentPlayer.getTerritories();
  for (auto &territory : territories) {
    // Reset selected
    territory->setSelected(false);
  }

  state.setTurn(state.getTurn() + 1);
}

Json::Value FinishTurnCommand::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;

  return newCommand;
}
