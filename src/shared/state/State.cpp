#include "State.h"

using namespace state;

State::State() {}

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

int State::nextTurn() {}

int State::getCurrentPlayerId() { return currentPlayerId; }

void State::setCurrentPlayerId(int cpi) { currentPlayerId = cpi; }

int State::getNbPlayers() { return nbPlayers; }

void State::setNbPlayers(int np) { nbPlayers = np; }

Board &State::getBoard() {}

std::vector<Territory> &State::getTerritories() {}

size_t State::addTerritory(Territory *t) {}

std::vector<Player> &State::getPlayers() {}

size_t State::addPlayer(Player *p) {}

State *const State::clone() {}

bool const State::equals(const State &state1) {}
