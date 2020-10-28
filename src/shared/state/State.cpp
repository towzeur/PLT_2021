#include "State.h"

using namespace state;

State::State(const State& state1) {
    
}

State::~State() {
    
}

void State::operator=(const State& state1) {
    
}

void State::setEnableCache(bool ec) {
    
}

void State::setEnableNotifications(bool en) {
    
}

void State::flush() {
    
}

bool State::getGameOver() {
    
}

void State::setGameOver(bool go) {
    
}

int State::getTurn() {
    
}

void State::setTurn(int turn) {
    
}

int State::nextTurn() {
    
}

int State::getCurrentPlayerId() {
    
}

void State::setCurrentPlayerId(int cpi) {
    
}

int State::getNbPlayers() {
    
}

void State::setNbPlayers(int np) {
    
}

Board& State::getBoard() {
    
}

std::vector<Territory>& State::getTerritories() {
    
}

size_t State::addTerritory(Territory* t) {
    
}

std::vector<Player>& State::getPlayers() {
    
}

size_t State::addPlayer(Player* p) {
    
}

State* const State::clone() {
    
}

bool const State::equals(const State& state1) {
    
}
