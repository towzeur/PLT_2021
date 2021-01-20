#include <iostream>
#include <unistd.h>

#include "Engine.h"

//#include "engine.h"
#include "state.h"
#include "utils.h"

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

using namespace engine;

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init(std::string map) {

  state::Board &board = this->currentState.getBoard();

  // load the map
  std::string rpath_map = utils::Utils::resolveRelative("res/map.txt");
  board.load(rpath_map);

  // set the turn
  this->currentState.setTurn(1);

  // add the neutral player
  std::shared_ptr<state::Player> p(new state::Player);
  p->setName("NEUTRAL");
  p->setStatus(state::PlayerStatus::NEUTRAL);
  this->currentState.addPlayer(p);

  // add the players
  std::string names[] = {"Badisse", "Nico", "Hicham", "Kaan"};
  for (auto &name : names) {
    std::shared_ptr<state::Player> p(new state::Player);
    p->setName(name);
    p->setStatus(state::PlayerStatus::PLAYING);
    this->currentState.addPlayer(p);
  }

  printf("DEBUG : !!!!\n");

  // get all the players
  std::vector<std::shared_ptr<state::Player>> players =
      this->currentState.getPlayers();

  // Init Territories
  for (auto &c : board.getCells()) { // loop through cell

    if (c->isAccessible()) {
      state::AccessibleCell *ac = (state::AccessibleCell *)c.get();
      int sid = ac->getEntity().getEntitySubTypeId();
      if (sid == state::EntitySubTypeId::FACILITY_CAPITAL) { // detect capital

        // retrieve the player
        if (ac->getPlayerId() == 0)
          continue; // neutral player
        std::shared_ptr<state::Player> p = players[ac->getPlayerId()];

        // create a territory
        std::shared_ptr<state::Territory> newTerritory(new state::Territory);
        newTerritory->setCapitalCoords(c->getRow(), c->getCol());
        newTerritory->addCell(c);

        // map it to the player
        p->addTerritory(newTerritory);
        ac->setTerritoryId(newTerritory->getUid());

        // propagate it
        this->propagateTerritory(c);
      }
    }
  }
}

int Engine::propagateTerritory(std::shared_ptr<state::Cell> c0) {
  printf("propagate\n");

  if (!c0->isAccessible())
    return -1;

  state::AccessibleCell *ac0 = (state::AccessibleCell *)c0.get();
  const int territory_id = ac0->getTerritoryId();
  const int player_id = ac0->getPlayerId();

  state::Board &board = this->currentState.getBoard();
  int n_row = board.getNRow(), n_col = board.getNCol();
  // printf("[DEBUG] (%d,%d)\n", n_row, n_col);

  // open and close for the tree search
  std::vector<int> OPEN;
  bool *CLOSE = new bool[n_row * n_col];
  for (int i = 0; i < n_row * n_col; i++)
    CLOSE[i] = false;

  OPEN.push_back(c0->getRow() * n_col + c0->getCol()); // add the first elt
  while (!OPEN.empty()) {                              // exploration loop

    int index = OPEN.back(); // take the first element

    if (!CLOSE[index]) { // not already explored
      int r0 = index / n_col, c0 = index % n_col;

      // explore his neighbor
      int r1, c1, index1;
      for (int d = 0; d < 6; ++d) {
        // generate his coords
        r1 = r0 + DIRECTIONS[d][0];
        c1 = c0 + DIRECTIONS[d][1];
        index1 = r1 * n_col + c1;

        // check if the pos is within the grid
        if ((r1 < 0 || r1 >= n_row) || (c1 < 0 || c1 >= n_col))
          continue;
        // skip if the cell is already explored
        if (CLOSE[index1])
          continue;
        // retrieve the cell
        std::shared_ptr<state::Cell> cell = board.get(r1, c1);
        if (!cell->isAccessible()) // skip if not accessible
          continue;

        // convert it to Accessible cell
        state::AccessibleCell *acell = (state::AccessibleCell *)cell.get();

        if (acell->getPlayerId() == player_id) { // BINGO

          acell->setTerritoryId(territory_id); // set the cell territory
          // add it to the territory vector

          OPEN.push_back(index1); // add the new node
        }

        // std::shared_ptr<state::AccessibleCell> acell(cell);
      }
    }

    OPEN.pop_back();     // remove it from OPEN
    CLOSE[index] = true; // add it to CLOSE
  }

  return 0;
}

void Engine::setCurrentState(state::State currentState) {
  this->currentState = currentState;
}

state::State &Engine::getCurrentState() { return this->currentState; }

void Engine::setRecord(Json::Value record) { this->record = record; }

Json::Value Engine::getRecord() { return this->record; }

void Engine::addCommand(std::unique_ptr<Command> ptr_cmd) {
  Json::Value newCommand = ptr_cmd->serialize();
  record["CommandArray"][record["Size"].asUInt()] = newCommand;
  record["Size"] = record["Size"].asUInt() + 1;
}

/**
 * @brief check if the move (r0, c0) to (r1, c1) is legal
 *
 * @param r0
 * @param c0
 * @param r1
 * @param c1
 * @return true
 * @return false
 */
bool Engine::action_map_valid(int r0, int c0, int r1, int c1) {
  state::Board &board = this->currentState.getBoard();
  int n_row = board.getNRow(), n_col = board.getNCol();

  // check that the two position are within the map
  if ((r0 < 0 || r0 >= n_row) || (c0 < 0 || c0 >= n_col))
    return false;
  if ((r1 < 0 || r1 >= n_row) || (c1 < 0 || c1 >= n_col))
    return false;

  // same cell
  if (r0 == r1 && c0 == c1)
    return false;

  // retrieve the two cell
  std::shared_ptr<state::Cell> cell0 = board.get(r0, c0);
  std::shared_ptr<state::Cell> cell1 = board.get(r1, c1);

  if (!cell0->isAccessible() || !cell1->isAccessible())
    return false;

  return true;
}

int Engine::action_map(int r0, int c0, int r1, int c1) {
  if (action_map_valid(r0, c0, r1, c1))
    return 0;

  state::Board &board = this->currentState.getBoard();
  state::AccessibleCell *acell0 = board.get(r0, c0)->castAccessible();
  state::AccessibleCell *acell1 = board.get(r1, c1)->castAccessible();

  return 1;
}