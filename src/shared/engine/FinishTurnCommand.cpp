#include "FinishTurnCommand.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

FinishTurnCommand::FinishTurnCommand() { this->commandTypeId = FINISH_TURN; }

void FinishTurnCommand::execute(state::State &state) {

  std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();
  for (std::shared_ptr<state::Cell> &soldier : cells) {
    printf("ns\n");
    if (soldier->getEntity().isSoldier() && soldier->isAccessible()) {
      // Reset PA of all soldiers at the end of the turn
      printf("bonjour\n");
      printf("c= %d r= %d\n", soldier->getCol(), soldier->getRow());
      soldier->getEntity().setPA(1);
    }
  }
  printf("bbbb\n");

  std::vector<std::shared_ptr<state::Territory>> territories =
      currentPlayer.getTerritories();
  printf("jjj\n");
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