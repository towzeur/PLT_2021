#include "MoveCommand.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

MoveCommand::MoveCommand(state::Cell &soldierTarget, state::Cell &cellTarget)
    : soldierTarget(soldierTarget), cellTarget(cellTarget) {
  this->commandTypeId = MOVE;
}

void MoveCommand::execute(state::State &state) {
  std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();

  if (cellTarget.isAccessible() &&
      soldierTarget.getEntity().getEntityTypeId() == state::SOLDIER) {
    // Check if the move is on the same territory
    if (this->cellTarget.getPlayerId() == this->soldierTarget.getPlayerId()) {
      // Check if he try to move a soldier on one of his own facility
      if (this->cellTarget.getEntity().getEntityTypeId() ==
          state::EntityTypeId::FACILITY) {
        std::cout << "Impossible action: your can't move a soldier on "
                     "one of your facilitys"
                  << std::endl;
      }
      // Check if he try to do a fusion
      else if (this->cellTarget.getEntity().getEntityTypeId() ==
               state::EntityTypeId::SOLDIER) {
        int newAttack = this->cellTarget.getEntity().getAttack() +
                        soldierTarget.getEntity().getAttack();
        int newDefense = this->cellTarget.getEntity().getDefense() +
                         soldierTarget.getEntity().getDefense();
        if (newAttack > 4 || newDefense > 4) {

          std::cout << "Impossible action: the result of your fusion "
                       "can't give a soldier with an attack or a defense "
                       "superior at 4"
                    << std::endl;

        }
        // Fusion
        else {

          if (newAttack == 2 && newDefense == 2) {
            std::shared_ptr<state::Entity> spearman(new state::Soldier(
                state::EntityTypeId::SOLDIER, state::SoldierTypeId::SPEARMAN,
                newAttack, newDefense));
            this->cellTarget.setEntity(*spearman);
            std::shared_ptr<state::Entity> empty(new state::Empty(
                state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID));
            soldierTarget.setEntity(*empty);
          } else if (newAttack == 3 && newDefense == 3) {
            std::shared_ptr<state::Entity> knight(new state::Soldier(
                state::EntityTypeId::SOLDIER, state::SoldierTypeId::KNIGHT,
                newAttack, newDefense));
            this->cellTarget.setEntity(*knight);
            std::shared_ptr<state::Entity> empty(new state::Empty(
                state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID));
            soldierTarget.setEntity(*empty);
          } else if (newAttack == 4 && newDefense == 4) {
            state::Entity *baron = new state::Soldier(
                state::EntityTypeId::SOLDIER, state::SoldierTypeId::BARON,
                newAttack, newDefense);
            this->cellTarget.setEntity(*baron);
            std::shared_ptr<state::Entity> empty(new state::Empty(
                state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID));
            soldierTarget.setEntity(*empty);
          } else {
            std::cout << "Error fusion" << std::endl;
          }
        }

      }
      // Cut a tree on his own territory
      else if (this->cellTarget.getEntity().getEntityTypeId() ==
               state::EntityTypeId::TREE) {
        soldierTarget.getEntity().setPA(0);
        this->cellTarget.setEntity(soldierTarget.getEntity());
        std::shared_ptr<state::Entity> empty(new state::Empty(
            state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID));
        soldierTarget.setEntity(*empty);
      }
      // move on the same territory
      else {
        this->cellTarget.setEntity(soldierTarget.getEntity());
        std::shared_ptr<state::Entity> empty(new state::Empty(
            state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID));
        soldierTarget.setEntity(*empty);
      }
    }
    // Check if he try to conquere a new territory
    else {

      if (soldierTarget.getEntity().getAttack() <
          this->cellTarget.getEntity().getDefense()) {

        std::cout << "Impossible action: soldier attack must be superior or "
                     "equal to cell entity defense"
                  << std::endl;
      }
      // Conquere a cell
      else {
        soldierTarget.getEntity().setPA(0);
        this->cellTarget.setTerritoryId(soldierTarget.getTerritoryId());
        this->cellTarget.setPlayerId(soldierTarget.getPlayerId());
        std::shared_ptr<state::Entity> empty(new state::Empty(
            state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID));
        soldierTarget.setEntity(*empty);
      }
    }
  } else {
    std::cout << "Impossible action: innaccessible cell or not Soldier"
              << std::endl;
  }
}

Json::Value MoveCommand::serialize() {
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;
  newCommand["entityUid"] = soldierTarget.getEntity().getUid();
  newCommand["targetRow"] = cellTarget.getRow();
  newCommand["targetCol"] = cellTarget.getCol();

  return newCommand;
}