#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

#define CELL_INCOME 3
#define PEASANT_COST 2
#define SPEARMAN_COST 5
#define KNIGHT_COST 10
#define BARON_COST 15

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

  // update data
  for (auto player : currentState.getPlayers()) {
    for (auto territory : player->getTerritories()) {
      size_t cellNb = territory->getCells().size();
      territory->setIncome(CELL_INCOME * cellNb);

      size_t peasantNb = 0;
      size_t spearmanNb = 0;
      size_t knightNb = 0;
      size_t baronNb = 0;
      for (auto cell : territory->getCells()) {
        if (cell->getEntity().getEntityTypeId() == state::SOLDIER) {
          if (cell->getEntity().getSubTypeId() == 1) {
            peasantNb++;
          } else if (cell->getEntity().getSubTypeId() == 2) {
            spearmanNb++;
          } else if (cell->getEntity().getSubTypeId() == 3) {
            knightNb++;
          } else if (cell->getEntity().getSubTypeId() == 4) {
            baronNb++;
          } else {
            std::cout << "Error subtypeId" << std::endl;
          }
        }
      }

      territory->setWages(peasantNb * PEASANT_COST +
                          spearmanNb * SPEARMAN_COST + knightNb * KNIGHT_COST +
                          baronNb * BARON_COST);

      territory->setSavings(territory->getSavings() + territory->getIncome() -
                            territory->getWages());
    }
  }
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