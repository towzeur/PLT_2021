#include <iostream>
#include <unistd.h>

#include "ActionSelectTerritory.h"

//#include "engine.h"
using namespace engine;

ActionSelectTerritory::ActionSelectTerritory() {}

ActionSelectTerritory::ActionSelectTerritory(int pId, int r0, int c0)
    : Action(pId, ActionId::SELECT_TERRITORY), r0(r0), c0(c0) {}

Json::Value ActionSelectTerritory::serialize() {
  Json::Value ser;
  ser["player_id"] = this->player_id;
  ser["action_id"] = (int)this->action_id;
  ser["r0"] = this->r0;
  ser["c0"] = this->c0;
  return ser;
}

void ActionSelectTerritory::deserialize(Json::Value &ser) {
  this->action_id = ActionId(ser["action_id"].asInt());
  this->player_id = ser["player_id"].asInt();
  this->r0 = ser["r0"].asInt();
  this->c0 = ser["c0"].asInt();
}

bool ActionSelectTerritory::isLegal(state::State &s) { return true; }

Json::Value ActionSelectTerritory::execute(state::State &s) {
  Json::Value out = Json::Value::null;
  state::Board &board = s.getBoard();
  std::shared_ptr<state::Cell> cell = board.get(r0, c0);

  // if (!cell->isAccessible()){}
  // return;

  state::AccessibleCell *ac = cell->castAccessible();
  printf("////////////////////////////////////\n");
  ac->print();
  printf("////////////////////////////////////\n");

  std::shared_ptr<state::Player> p = s.getPlayer(ac->getPlayerId());
  std::shared_ptr<state::Territory> t = p->findTerritory(ac->getTerritoryId());

  if (t) {
    printf("---------------------------------------------\n");
    printf("TERRITORY : %d, size=%d, player_id=%d\n", t->getUid(), t->getSize(),
           p->getUid());
    printf("Savings : %d\n", t->computeSavings());
    printf("Income  : %d\n", t->computeIncome());
    printf("Wages   : %d\n", t->computeWages());
    printf("Balance : %d\n", t->computeBalance());
    printf("---------------------------------------------\n");
  }
  return out;
}

void ActionSelectTerritory::print() {
  printf("[ActionSelectTerritory] player_id=%d : (%d, %d) \n", player_id, r0,
         c0);
}

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