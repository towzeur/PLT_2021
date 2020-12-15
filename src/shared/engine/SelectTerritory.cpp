#include "SelectTerritoryCommand.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

SelectTerritoryCommand::SelectTerritoryCommand(state::Territory &target)
    : target(target) {
  this->commandTypeId = SELECT_TERRITORY;
}

void SelectTerritoryCommand::execute(state::State &state) {

  for (auto &territory : currentPlayer.getTerritories()) {

    if (territory->getUid() == this->target.getUid()) {
      if (territory->isSelected() == true) {
        territory->setSelected(false);
        printf("oo\n");
      } else {
        territory->setSelected(true);
        printf("pp\n");
      }
    } else {
      territory->setSelected(false);
      printf("cc\n");
    }
  }
}

Json::Value SelectTerritoryCommand::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;
  newCommand["entityUid"] = target.getUid();

  return newCommand;
}