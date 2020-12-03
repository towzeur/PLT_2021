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

std::vector<std::unique_ptr<Player>> State::getPlayers() {
  return move(players);
}

size_t State::addPlayer(std::unique_ptr<Player> p) {
  players.push_back(move(p));
  return players.size();
}

Territory getTerritorySelected() {}

State *const State::clone() {}

bool const State::equals(const State &state1) {}
