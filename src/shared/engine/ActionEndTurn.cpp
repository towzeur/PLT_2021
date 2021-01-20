#include "ActionEndTurn.h"
//#include "engine.h"

#include <iostream>
#include <unistd.h>

using namespace engine;

ActionEndTurn::ActionEndTurn() {}

Json::Value ActionEndTurn::serialize() {}

void ActionEndTurn::deserialize(Json::Value &ser) {}

void ActionEndTurn::execute(state::State &state) {}

void ActionEndTurn::print() {}

/*
void ActionEndTurn::execute(state::State &state) {

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

Json::Value ActionEndTurn::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;

  return newCommand;
}
*/