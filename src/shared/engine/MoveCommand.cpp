#include "MoveCommand.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

MoveCommand::MoveCommand(state::Soldier &soldierTarget,
                         state::AccessibleCell &cellTarget)
    : soldierTarget(soldierTarget), cellTarget(cellTarget) {
  this->commandTypeId = MOVE;
}

void MoveCommand::execute(state::State &state) {
  std::vector<std::unique_ptr<state::Cell>> &cells =
      state.getBoard().getCells();

  if (cellTarget.isAccessible()) {
    for (std::unique_ptr<state::Cell> &soldier : cells) {

      if (soldier->getEntity().getUid() == this->soldierTarget.getUid()) {
        if (soldier->getEntity().getAttack() <
            this->cellTarget.getEntity().getDefense()) {
          std::cout << "Impossible action: soldier attack must be superior or "
                       "equal to cell entity defense"
                    << std::endl;
          break;
        } else {
          soldier->setRow(this->cellTarget.getRow());
          soldier->setCol(this->cellTarget.getCol());
          break;
        }
      }
    }
  } else {
    std::cout << "Impossible action: innaccessible cell" << std::endl;
  }
}

Json::Value MoveCommand::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;
  newCommand["entityUid"] = soldierTarget.getUid();
  newCommand["targetRow"] = cellTarget.getRow();
  newCommand["targetCol"] = cellTarget.getCol();

  return newCommand;
}