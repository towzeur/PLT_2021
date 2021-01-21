#include <iostream>
#include <unistd.h>

#include "ActionSelectTerritory.h"

//#include "engine.h"

using namespace engine;

ActionSelectTerritory::ActionSelectTerritory() {}

Json::Value ActionSelectTerritory::serialize() {}

void ActionSelectTerritory::deserialize(Json::Value &ser) {}

bool ActionSelectTerritory::isLegal(state::State &s) {}

void ActionSelectTerritory::execute(state::State &s) {}

void ActionSelectTerritory::print() {}

/*
void ActionSelectTerritory::execute(state::State &state) {

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

Json::Value ActionSelectTerritory::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;
  newCommand["entityUid"] = target.getUid();

  return newCommand;
}
*/