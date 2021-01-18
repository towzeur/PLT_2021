#include <iostream>
#include <unistd.h>

#include "Engine.h"
//#include "engine.h"
#include "utils/Utils.h"

using namespace engine;

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {

  // load the map
  std::string rpath_map = utils::Utils::resolveRelative("res/map.txt");
  this->currentState.getBoard().load(rpath_map);

  // set names
  std::string names[] = {"Badisse", "Nico", "Hicham", "Kaan"};
  for (auto &name : names) {
    std::shared_ptr<state::Player> p(new state::Player);
    p->setName(name);
    this->currentState.addPlayer(p);
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
  bool neighborCellExist = true;
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
          printf("cpCol: %d   cpRow: %d\ncCol: %d   cRow: %d\n", cp->getCol(),
                 cp->getRow(), allPlayerCells[i]->getCol(),
                 allPlayerCells[i]->getRow());
          if (cp->getCol() == allPlayerCells[i]->getCol() &&
              cp->getRow() == allPlayerCells[i]->getRow()) {
            printf("same\n");
          } else if (cp->getCol() == allPlayerCells[i]->getCol() &&
                     cp->getRow() == allPlayerCells[i]->getRow() + 1) {
            printf("haut gauche\n");
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() &&
                     cp->getRow() == allPlayerCells[i]->getRow() - 1) {
            printf("bas gauche\n");
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() + 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow() - 1) {
            printf("haut droite\n");
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() + 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow() + 1) {
            printf("bas droite\n");
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() + 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow()) {
            printf("droite\n");
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
          } else if (cp->getCol() == allPlayerCells[i]->getCol() - 1 &&
                     cp->getRow() == allPlayerCells[i]->getRow()) {
            printf("gauche\n");
            p->getTerritories()[0]->addCell(allPlayerCells[i]);
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