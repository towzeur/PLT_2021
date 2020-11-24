#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {

  std::string texts[] = {"Badisse", "Nico", "Hicham", "Kaan"};
  state::Player p;
  for (const std::string &text : texts) {
    p = state::Player();
    p.setName(text);
    this->currentState.addPlayer(&p);
  }

  try {
    this->currentState.getBoard().load("../../../res/map.txt");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    this->currentState.getBoard().load("res/map.txt");
  }

  this->currentState.setTurn(1);
  this->currentState.getPlayers()[0].setStatus(state::PLAYING);
}

void Engine::setCurrentState(state::State currentState) {
  this->currentState = currentState;
}

state::State &Engine::getCurrentState() { return this->currentState; }

void Engine::setRecord(Json::Value record) { this->record = record; }

Json::Value Engine::getRecord() { return this->record; }
