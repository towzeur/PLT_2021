#include "BuyEntityCommand.h"
//#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

BuyEntityCommand::BuyEntityCommand(state::Entity &target,
                                   state::Cell &cellTarget)
    : target(target), cellTarget(cellTarget) {
  this->commandTypeId = BUY_SOLDIER;
}

void BuyEntityCommand::execute(state::State &state) {
  std::vector<std::shared_ptr<state::Cell>> cells = state.getBoard().getCells();

  if (cellTarget.isAccessible() && target.getEntityTypeId() == state::SOLDIER) {
    // Check if the move is on the same territory
    if (this->cellTarget.getPlayerId() == currentPlayer.getUid()) {
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
        int newAttack =
            this->cellTarget.getEntity().getAttack() + target.getAttack();
        int newDefense =
            this->cellTarget.getEntity().getDefense() + target.getDefense();
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
          } else if (newAttack == 3 && newDefense == 3) {
            std::shared_ptr<state::Entity> knight(new state::Soldier(
                state::EntityTypeId::SOLDIER, state::SoldierTypeId::KNIGHT,
                newAttack, newDefense));
            this->cellTarget.setEntity(*knight);
          } else if (newAttack == 4 && newDefense == 4) {
            state::Entity *baron = new state::Soldier(
                state::EntityTypeId::SOLDIER, state::SoldierTypeId::BARON,
                newAttack, newDefense);
            this->cellTarget.setEntity(*baron);
          } else {
            std::cout << "Error fusion" << std::endl;
          }
        }

      }
      // Cut a tree on his own territory
      else if (this->cellTarget.getEntity().getEntityTypeId() ==
               state::EntityTypeId::TREE) {
        target.setPA(0);
        this->cellTarget.setEntity(target);
      }
      // move on the same territory
      else {
        this->cellTarget.setEntity(target);
      }
    }
    // Check if he try to conquere a new territory
    else {

      if (target.getAttack() < this->cellTarget.getEntity().getDefense()) {

        std::cout << "Impossible action: soldier attack must be superior or "
                     "equal to cell entity defense"
                  << std::endl;
      }
      // Conquere a cell
      else {
        target.setPA(0);
        // this->cellTarget.setTerritoryId(soldierTarget.getTerritoryId());
        this->cellTarget.setPlayerId(currentPlayer.getUid());
        this->cellTarget.setEntity(target);
      }
    }
  } else {
    std::cout << "Impossible action: innaccessible cell or not Soldier"
              << std::endl;
  }
}