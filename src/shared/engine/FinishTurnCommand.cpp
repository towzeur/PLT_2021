#include "FinishTurnCommand.h"
//#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

FinishTurnCommand::FinishTurnCommand() { this->commandTypeId = FINISH_TURN; }

void FinishTurnCommand::execute(state::State &state) {

  std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();
  for (std::shared_ptr<state::Cell> &cell : cells) {
    if (cell->getEntity().isSoldier()) {
      // Reset PA of all soldiers at the end of the turn
      cell->getEntity().setPA(1);
    }
  }

  std::vector<std::shared_ptr<state::Territory>> territories =
      currentPlayer.getTerritories();
  for (auto &territory : territories) {
    // Reset selected
    territory->setSelected(false);
  }

  state.setTurn(state.getTurn() + 1);
  if (state.getCurrentPlayerId() == state.getPlayers().size()) {
    state.setCurrentPlayerId(1);
  } else {
    state.setCurrentPlayerId(state.getCurrentPlayerId() + 1);
  }
}

Json::Value FinishTurnCommand::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;

  return newCommand;
}
