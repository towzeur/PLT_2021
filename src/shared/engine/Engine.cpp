#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

Engine::Engine() {}

Engine::~Engine() {}

void checkNeighbor() {}

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
  for (auto &c : this->currentState.getBoard().getCells()) {
    if (c->getEntity().getEntityTypeId() == state::EntityTypeId::FACILITY) {
      std::shared_ptr<state::Player> p = players[c->getPlayerId() - 1];
      if (c->getPlayerId() - 1 == 0) {
        p->setStatus(state::PLAYING);
      }
      std::shared_ptr<state::Territory> newTerritory(new state::Territory);
      int uid = newTerritory->getUid();
      newTerritory->setCapitalCoords(c->getRow(), c->getCol());
      newTerritory->addCell(c);
      p->addTerritory(newTerritory);
      c->setTerritoryId(uid);
    }
  }
  // Adding cells which compose the territory
  for (auto &p : this->currentState.getPlayers()) {
    neighborCellExist = true;
    std::vector<std::shared_ptr<state::Cell>> allPlayerCells;

    for (auto &c : this->currentState.getBoard().getCells()) {
      if (c->getPlayerId() == p->getUid()) {
        allPlayerCells.push_back(c);
      }
    }

    while (neighborCellExist) {
      if (allPlayerCells.size() == 0) {
        neighborCellExist = false;
      }
      for (size_t i = 0; i < allPlayerCells.size(); i++) {
        if (p->getTerritories()[0]->getCells().size() == 0) {
          neighborCellExist = false;
        }
        for (auto &cp : p->getTerritories()[0]->getCells()) {
          if (cp->getCol() == allPlayerCells[i]->getCol() &&
              cp->getRow() == allPlayerCells[i]->getRow() - 1) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() &&
                     cp->getRow() == allPlayerCells[i]->getRow() - 1) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
            allPlayerCells.push_back(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() &&
                     cp->getRow() == allPlayerCells[i]->getRow() + 1) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
            allPlayerCells.push_back(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() + 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow() - 1) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
            allPlayerCells.push_back(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() + 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow() + 1) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
            allPlayerCells.push_back(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() + 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow()) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
            allPlayerCells.push_back(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() - 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow()) {
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
            allPlayerCells.push_back(allPlayerCells[i]);
          } else {
            neighborCellExist = false;
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