#include <iostream>
#include <unistd.h>

#include "ActionSoldier.h"

using namespace engine;

ActionSoldier::ActionSoldier() {
  this->sub_action_id = ActionSoldierId::INVALID;
}

Json::Value ActionSoldier::serialize() {
  Json::Value ser;
  ser["player_id"] = this->player_id;
  ser["action_id"] = (int)this->action_id;
  ser["r0"] = this->r0;
  ser["c0"] = this->c0;
  ser["r1"] = this->r1;
  ser["c1"] = this->c1;
  return ser;
}

void ActionSoldier::deserialize(Json::Value &ser) {
  this->action_id = ActionId(ser["action_id"].asInt());
  this->player_id = ser["player_id"].asInt();
  this->r0 = ser["r0"].asInt();
  this->c0 = ser["c0"].asInt();
  this->r1 = ser["r1"].asInt();
  this->c1 = ser["c1"].asInt();
}

void ActionSoldier::execute(state::State &state) {}

void ActionSoldier::print() {
  printf("[ActionSoldier] player_id=%d : (%d, %d) => (%d, %d) \n", player_id,
         r0, c0, r1, c1);
}

bool ActionSoldier::isLegal(state::State &s) {
  state::Board &b = s.getBoard();
  int n_row = b.getNRow(), n_col = b.getNCol();

  // check if its turn and the if he still in game
  if ((s.getCurrentPlayerId() == this->player_id) &&
      s.getPlayer(this->player_id)->isPlaying())
    return false;

  // check that the two position are within the map
  // and that it's not two time the same cell
  if ((r0 < 0) || (r0 >= n_row) || (c0 < 0) || (c0 >= n_col) || (r1 < 0) ||
      (r1 >= n_row) || (c1 < 0) || (c1 >= n_col) || (r0 == r1 && c0 == c1))
    return false;

  // retrieve the two cell
  state::AccessibleCell *ac0 = b.get(r0, c0)->castAccessible();
  state::AccessibleCell *ac1 = b.get(r1, c1)->castAccessible();
  if (!ac0 || !ac1) // assert none of them is Inaccesible
    return false;

  state::Entity &e0 = ac0->getEntity();
  state::Entity &e1 = ac1->getEntity();

  // check that the first cell is a soldier and have sufficient PA
  if (!e0.isSoldier() || !e0.getActionPoint())
    return false;

  if (ac0->getPlayerId() == ac0->getPlayerId()) { // same player

    // the target cell must be on the same territory
    if (ac0->getTerritoryId() == ac0->getTerritoryId()) {
      if (e1.isEmpty())
        return isLegalMove(s);
      else if (e1.isTree())
        return isLegalAttack(s);
      else if (e1.isFacility())
        return false;
      else if (e1.isSoldier())
        return isLegalFusion(s);
      throw std::runtime_error("ActionSoldier isLegal : unknow Entity !");
    } else
      // the two cell bellong to the same player but on different territory
      return false;
  }

  // different player
  return isLegalAttack(s);
}

/**
 * @brief
 *
 * @param s
 * @return true
 * @return false
 */
bool ActionSoldier::isLegalMove(state::State &s) {
  this->sub_action_id = ActionSoldierId::MOVE;
  return true;
}

bool ActionSoldier::isLegalAttack(state::State &s) {
  this->sub_action_id = ActionSoldierId::ATTACK;
}

/**
 * @brief assert that the resulting man is not stronger than the stronger man
 *        available (BARON)
 *
 *        assertion : c0, c1 valid, same player_id, same territory
 *
 * @param s
 * @return true
 * @return false
 */
bool ActionSoldier::isLegalFusion(state::State &s) {
  this->sub_action_id = ActionSoldierId::FUSION;

  state::Board &b = s.getBoard();
  state::AccessibleCell *ac0 = b.get(r0, c0)->castAccessible();
  state::AccessibleCell *ac1 = b.get(r1, c1)->castAccessible();

  state::Entity &e0 = ac0->getEntity();
  state::Entity &e1 = ac1->getEntity();

  int new_strength = e0.getStrength() + e1.getStrength();
  return state::Entity::isValidStrength(new_strength);
}

/*
void ActionSoldier::execute(state::State &state) {

  std::vector<std::shared_ptr<state::Cell>> cells =
state.getBoard().getCells();

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
                    state::EntityTypeId::SOLDIER,
state::SoldierTypeId::KNIGHT, newAttack, newDefense);
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
            state::Entity *empty = new
state::Empty(state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID);
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
            state::Entity *empty = new
state::Empty(state::EntityTypeId::EMPTY, state::EmptyTypeId::VOID);
            soldier->setEntity(*empty);
          }
        }
      }
    }
  }

  else {
    std::cout << "Impossible action: innaccessible cell" << std::endl;
  }

}
*/
