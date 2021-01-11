#include "State.h"

using namespace state;

State::State() : gameOver(false), turn(0), currentPlayerId(0) {}

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

Board &State::getBoard() { return this->board; }

void State::setBoard(Board& board) { this->board = board; }

std::vector<std::shared_ptr<Player>> State::getPlayers() { return players; }

void State::addPlayer(std::shared_ptr<Player> p) { players.push_back(move(p)); }

Territory getTerritorySelected() {}

State *const State::clone() {}

bool const State::equals(const State &state1) {}
