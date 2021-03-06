#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

#include "Action.h"
#include "Engine.h"

//#include "engine.h"
#include "state.h"
#include "utils.h"

using namespace engine;

//   NW N NE
//   W  .  E
//   SW S SE
static const int DIRECTIONS[6][2] = {
    {-1, +1}, // NE
    {-1, 0},  // N
    {-1, -1}, // NW
    {0, -1},  // SW
    {1, 0},   // S
    {0, 1}    // SE
};
// -----------------------------------------------------------------------------

bool compare_player_id(std::shared_ptr<state::Cell> cell, int player_id) {
  // skip if not accessible
  if (!cell->isAccessible())
    return false;
  // convert it to Accessible cell
  state::AccessibleCell *acell = cell->castAccessible();
  if (acell->getPlayerId() == player_id) {
    printf("TEAM JBZZ\n");
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init(std::string map) {

  state::Board &board = this->currentState.getBoard();

  // load the map
  std::string rpath_map = utils::Utils::resolveRelative(map);
  board.load(rpath_map);

  currentState.init();

  // add the players
  std::string names[] = {"Badisse", "Nico", "Hicham", "Kaan"};
  for (auto &name : names) {
    this->currentState.addPlayer(name);
  }

  // Init Territories
  std::shared_ptr<state::Player> p;
  std::shared_ptr<state::Territory> newTerritory;
  for (auto &c : board.getCells()) { // loop through cell

    if (c->isAccessible()) {
      state::AccessibleCell *ac = (state::AccessibleCell *)c.get();
      int sid = ac->getEntity().getEntitySubTypeId();

      // capital and not the neutral player
      if (sid == state::EntitySubTypeId::FACILITY_CAPITAL &&
          ac->getPlayerId() != 0) {
        p = currentState.getPlayer(ac->getPlayerId());

        newTerritory = p->createTerritory();
        newTerritory->addCell(c);
        ac->setTerritoryId(newTerritory->getUid());

        // propagate it
        std::function<bool(std::shared_ptr<state::Cell>)> f1 =
            std::bind(&compare_player_id, std::placeholders::_1, p->getUid());
        std::vector<std::shared_ptr<state::Cell>> t_cells =
            this->propagate(c, f1);
        printf("[TERRITORY] %d \n", t_cells.size());

        for (auto &t_cell : t_cells) {
          printf("(%d, %d)", t_cell->getRow(), t_cell->getCol());
        }

        // acell->setTerritoryId(territory_id); // set the cell territory
      }
    }
  }
}

state::State &Engine::getCurrentState() { return this->currentState; }

void Engine::setRecord(Json::Value record) { this->record = record; }

Json::Value Engine::getRecord() { return this->record; }

/*
void Engine::addCommand(std::unique_ptr<Command> ptr_cmd) {
  Json::Value newCommand = ptr_cmd->serialize();
  record["CommandArray"][record["Size"].asUInt()] = newCommand;
  record["Size"] = record["Size"].asUInt() + 1;
}
*/

void Engine::processAction(Json::Value &ser) {
  printf("Engine processAction\n");

  // retrieve the right action
  engine::ActionId a_id = (engine::ActionId)ser["action_id"].asInt();
  Action *action = Action::getAction(a_id);

  action->deserialize(ser);
  action->print();

  if (action->isLegal(currentState)) {
    action->execute(currentState);
    printf("legal\n");
  } else {
    printf("illegal\n");
  }
}

/**
 * @brief
 *
 * @param c0
 * @param f
 * @return std::vector<std::shared_ptr<state::Cell>>
 */
std::vector<std::shared_ptr<state::Cell>>
Engine::propagate(std::shared_ptr<state::Cell> cell0,
                  std::function<bool(std::shared_ptr<state::Cell>)> f) {
  printf("propagate\n");
  std::vector<std::shared_ptr<state::Cell>> out;
  state::Board &board = this->currentState.getBoard();
  const int n_row = board.getNRow(), n_col = board.getNCol();

  // open and close for the tree search
  std::vector<int> OPEN;
  bool *CLOSE = new bool[n_row * n_col];
  for (int i = 0; i < n_row * n_col; i++)
    CLOSE[i] = false;

  // add the first elt
  int index = board.sub2ind(cell0->getRow(), cell0->getCol());
  OPEN.push_back(index);

  // exploration loop
  while (!OPEN.empty()) {
    index = int(OPEN.back()); // take the last element
    OPEN.pop_back();          // remove it from OPEN
    if (!CLOSE[index]) {
      // add it to the current list
      std::pair<int, int> coords = board.ind2sub(index); // (r0, c0)
      std::shared_ptr<state::Cell> cell = board.get(index);
      out.push_back(cell);

      // explore his neighbors (up to 6)
      for (auto &cell1 : board.getNeighbors(coords.first, coords.second)) {
        int index1 = board.sub2ind(cell1->getRow(), cell1->getCol());
        if (!CLOSE[index1] && f(cell1))
          OPEN.push_back(index1);
      }
      CLOSE[index] = true; // add it to CLOSE
    }
  }

  return out;
}