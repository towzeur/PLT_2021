#include <stdexcept>

#include "State.h"

using namespace state;

State::State() : gameOver(false), turn(0), currentPlayerId(0) {}

State::State(const State &state1) {}

State::~State() {}

void State::operator=(const State &state1) {}

/**
 * @brief init the state
 *
 */
void State::init() {
  setTurn(1);

  // add the neutral player
  players.clear();
  std::shared_ptr<state::Player> p = addPlayer("NEUTRAL");
  p->setStatus(PlayerStatus::NEUTRAL);
}

void State::setEnableCache(bool ec) {}

void State::setEnableNotifications(bool en) {}

void State::flush() {}

bool State::getGameOver() { return gameOver; }

void State::setGameOver(bool go) { gameOver = go; }

int State::getTurn() { return turn; }

void State::setTurn(int turn) { this->turn = turn; }

int State::nextTurn() { return this->turn + 1; }

int State::getCurrentPlayerId() { return currentPlayerId; }

void State::setCurrentPlayerId(int cpi) { currentPlayerId = cpi; }

Board &State::getBoard() { return this->board; }

void State::setBoard(Board &board) { this->board = board; }

std::vector<std::shared_ptr<Player>> State::getPlayers() { return players; }

std::shared_ptr<Player> State::getPlayer(int playerId) {
  try {
    return players.at(playerId);
  } catch (std::out_of_range const &exc) {
    // std::cout << exc.what() << '\n';
    throw std::runtime_error("getPlayer : unknown playerId !");
  }
}

void State::addPlayer(std::shared_ptr<Player> p) { players.push_back(p); }

/**
 * @brief create and return a player with the given name
 *
 * @param player_name
 * @return std::shared_ptr<Player>
 */
std::shared_ptr<Player> State::addPlayer(std::string player_name) {
  std::shared_ptr<state::Player> p(new state::Player);
  p->setName(player_name);
  p->setStatus(PlayerStatus::PLAYING);
  this->addPlayer(p);
  return p;
}

Territory getTerritorySelected() {}

State *const State::clone() {}

bool const State::equals(const State &state1) {}
