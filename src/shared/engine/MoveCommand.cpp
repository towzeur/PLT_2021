#include "MoveCommand.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

MoveCommand::MoveCommand() { this->commandTypeId = MOVE; }

void MoveCommand::execute(state::State &state) {
  /*
  std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();

  if (cellTarget.isAccessible()) {
    for (std::shared_ptr<state::Cell> &soldier : cells) {
      // Catch the cell of the soldier
      if (soldier->getEntity().getUid() == this->soldierTarget.getUid()) {
        // Check if the move is on the same territory
        if (this->cellTarget.getPlayerId() == soldier->getPlayerId()) {
          // Check if he try to move a soldier on one of his own facility
          if (this->cellTarget.getEntity().getEntityTypeId() ==
              state::EntityTypeId::FACILITY) {
            std::cout << "Impossible action: your can't move a soldier on "
                         "one of your facilitys"
                      << std::endl;
            break;
          }
          // Check if he try to do a fusion
          else if (this->cellTarget.getEntity().getEntityTypeId() ==
                   state::EntityTypeId::SOLDIER) {
            int newAttack = this->cellTarget.getEntity().getAttack() +
                            soldier->getEntity().getAttack();
            int newDefense = this->cellTarget.getEntity().getDefense() +
                             soldier->getEntity().getDefense();
            if (newAttack > 4 || newDefense > 4) {
              std::cout << "Impossible action: the result of your fusion "
                           "can't give a soldier with an attack or a defense "
                           "superior at 4"
                        << std::endl;
              break;
            }
            // Fusion
            else {
              if (newAttack == 2 && newDefense == 2) {
                state::Entity *spearman = new state::Soldier(
                    state::EntityTypeId::SOLDIER,
                    state::SoldierTypeId::SPEARMAN, newAttack, newDefense);
                this->cellTarget.setEntity(*spearman);
                state::Entity *empty = new state::Empty(
                    state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID);
                soldier->setEntity(*empty);
              } else if (newAttack == 3 && newDefense == 3) {
                state::Entity *knight = new state::Soldier(
                    state::EntityTypeId::SOLDIER, state::SoldierTypeId::KNIGHT,
                    newAttack, newDefense);
                this->cellTarget.setEntity(*knight);
                state::Entity *empty = new state::Empty(
                    state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID);
                soldier->setEntity(*empty);
              } else if (newAttack == 4 && newDefense == 4) {
                state::Entity *baron = new state::Soldier(
                    state::EntityTypeId::SOLDIER, state::SoldierTypeId::BARON,
                    newAttack, newDefense);
                this->cellTarget.setEntity(*baron);
                state::Entity *empty = new state::Empty(
                    state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID);
                soldier->setEntity(*empty);
              } else {
                std::cout << "Error fusion" << std::endl;
                break;
              }
            }
          }
          // Cut a tree on his own territory
          else if (this->cellTarget.getEntity().getEntityTypeId() ==
                   state::EntityTypeId::TREE) {

            state::Soldier &s =
                dynamic_cast<state::Soldier &>(soldier->getEntity());
            s.setPA(0);
            this->cellTarget.setEntity(s);
            state::Entity *empty = new state::Empty(state::EntityTypeId::EMPTY,
                                                    state::EmptyTypeId::VOID);
            soldier->setEntity(*empty);
          }
        }

        // Check if he try to conquere a new territory
        else {
          if (soldier->getEntity().getAttack() <
              this->cellTarget.getEntity().getDefense()) {
            std::cout
                << "Impossible action: soldier attack must be superior or "
                   "equal to cell entity defense"
                << std::endl;
            break;
          }
          // Conquere a cell
          else if (this->cellTarget.getEntity().getEntityTypeId() ==
                   state::EntityTypeId::EMPTY) {
            state::Soldier &s =
                dynamic_cast<state::Soldier &>(soldier->getEntity());
            s.setPA(0);
            this->cellTarget.setEntity(s);
            this->cellTarget.setTerritoryId(soldier->getTerritoryId());
            this->cellTarget.setPlayerId(soldier->getPlayerId());
            state::Entity *empty = new state::Empty(state::EntityTypeId::EMPTY,
                                                    state::EmptyTypeId::VOID);
            soldier->setEntity(*empty);
          }
        }
      }
    }
  }

  else {
    std::cout << "Impossible action: innaccessible cell" << std::endl;
  }
  */
}

Json::Value MoveCommand::serialize() {
  /*
  Json::Value newCommand;
  newCommand["id"] = this->commandTypeId;
  newCommand["entityUid"] = soldierTarget.getUid();
  newCommand["targetRow"] = cellTarget.getRow();
  newCommand["targetCol"] = cellTarget.getCol();

  return newCommand;
  */
}