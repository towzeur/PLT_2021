#include "State.h"

using namespace state;

State::State() : gameOver(false), turn(0), currentPlayerId(0), nbPlayers(0) {}

State::State(const State &state1) {}

State::~State() {}

void State::operator=(const State &state1) {}

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

int State::getNbPlayers() { return nbPlayers; }

void State::setNbPlayers(int np) { nbPlayers = np; }

Board &State::getBoard() { return this->board; }

void State::setBoard(Board& board) { this->board = board; }

std::vector<Territory> &State::getTerritories() { return territories; }

size_t State::addTerritory(Territory *t) {
  territories.push_back(*t);
  return territories.size();
}

std::vector<Player> &State::getPlayers() { return players; }

size_t State::addPlayer(Player *p) {
  players.push_back(*p);
  return players.size();
}

Territory getTerritorySelected() {}

State *const State::clone() {}

bool const State::equals(const State &state1) {}
