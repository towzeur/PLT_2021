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

  for (auto &name : names) {
    std::shared_ptr<state::Player> p(new state::Player);
    p->setName(name);
    this->currentState.addPlayer(p);
  }

  try {
    this->currentState.getBoard().load("../../../res/map.txt");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    this->currentState.getBoard().load("res/map.txt");
  }

  // Init Territories
  // Creation

  std::vector<std::shared_ptr<state::Player>> players =
      this->currentState.getPlayers();
  for (auto &c : move(this->currentState.getBoard().getCells())) {
    if (c->getEntity().getEntityTypeId() == state::EntityTypeId::FACILITY) {
      std::shared_ptr<state::Player> p = players[c->getPlayerId() - 1];
      if (c->getPlayerId() - 1 == 0) {
        p->setStatus(state::PLAYING);
      }
      std::unique_ptr<state::Territory> newTerritory(new state::Territory);
      int uid = newTerritory->getUid();
      newTerritory->setCapitalCoords(c->getRow(), c->getCol());
      p->addTerritory(move(newTerritory));
      c->setTerritoryId(uid);
    }
  }
  // Adding cells which compose the territory
  for (auto &p : this->currentState.getPlayers()) {
    printf("ok1\n");

    std::vector<std::shared_ptr<state::Cell>> allPlayerCells;
    for (auto &c : this->currentState.getBoard().getCells()) {
      if (c->getPlayerId() == p->getUid()) {
        allPlayerCells.push_back(c);
      }
    }
    printf("ok2\n");

    while (neighborCellExist) {
      for (auto &c : allPlayerCells) {
        for (auto &cp : p->getTerritories()[0]->getCells()) {
          if (cp->getCol() == c->getCol() && cp->getRow() == c->getRow() - 1) {
            p->getTerritories()[0]->addCell(c);
          }
        }
      }
    }
  }

  this->currentState.setTurn(1);
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