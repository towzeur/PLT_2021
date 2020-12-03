#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {

  std::string names[] = {"Badisse", "Nico", "Hicham", "Kaan"};
  bool neighborCellExist = true;

  for (const std::string &name : names) {
    std::unique_ptr<state::Player> p;
    p->setName(name); // Fatal error test
    this->currentState.addPlayer(move(p));
  }

  try {
    this->currentState.getBoard().load("../../../res/map.txt");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    this->currentState.getBoard().load("res/map.txt");
  }

  // Init Territories
  // Creation
  for (auto &c : move(this->currentState.getBoard().getCells())) {
    if (c->getEntity().getEntityTypeId() == state::EntityTypeId::FACILITY) {
      std::unique_ptr<state::Territory> newTerritory;
      newTerritory->setCapitalCoords(c->getRow(), c->getCol());
      this->currentState.getPlayers()[c->getPlayerId()]->addTerrotory(
          move(newTerritory));
      c->setTerritoryId(newTerritory->getUid());
    }
  }
  // Adding cells which compose the territory
  for (auto &p : this->currentState.getPlayers()) {
    std::vector<std::unique_ptr<state::Cell>> allPlayerCells;
    for (auto &c : move(this->currentState.getBoard().getCells())) {
      if (c->getPlayerId() == p->getUid()) {
        allPlayerCells.push_back(move(c));
      }
    }
    while (neighborCellExist) {
      for (auto &c : move(allPlayerCells)) {
        for (auto &cp : move(p->getTerritories()[0]->getCells())) {
          if (cp->getCol() == c->getCol() && cp->getRow() == c->getRow() - 1) {
            p->getTerritories()[0]->addCell(move(c));
          }
        }
      }
    }
  }

  this->currentState.setTurn(1);
  this->currentState.getPlayers()[0]->setStatus(state::PLAYING);
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