#include "BuyEntityCommand.h"
//#include "engine.h"
#include <iostream>
#include <unistd.h>

#define BUY_PEASANT_COST 10

using namespace engine;

BuyEntityCommand::BuyEntityCommand(state::Entity &target) : target(target) {
  this->commandTypeId = BUY_SOLDIER;
}

void BuyEntityCommand::execute(state::State &state) {
  bool territorySelected = false;
  bool emptyCell = false;
  // check if a territory is selected
  for (auto territory : currentPlayer.getTerritories()) {
    if (territory->isSelected()) {
      territorySelected = true;
      // check if he has enough money
      if (territory->getSavings() < BUY_PEASANT_COST) {
        std::cout << "You don't have enough money" << std::endl;
      } else {
        // put the entity on a random cell on the territory
        for (auto cell : territory->getCells()) {
          if (cell->getEntity().getEntityTypeId() == state::EMPTY) {
            emptyCell = true;
            cell->setEntity(target);
            territory->setSavings(territory->getSavings() - BUY_PEASANT_COST);
            break;
          }
        }
        break;
      }
    }
  }

  if (territorySelected == false) {
    std::cout << "You must select a territory first" << std::endl;
  }

  if (emptyCell == false) {
    std::cout << "No empty cell avalaible" << std::endl;
  }
}