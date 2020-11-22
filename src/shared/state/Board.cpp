#include "Board.h"
#include "state.h"
#include <fstream>
#include <iostream>
#include <memory>

#define NB_PLAYER_MAX 6

using namespace state;

Board::Board() : nRow(20), nCol(20) {}

Board::Board(const Board &board1) {}

Board::~Board() {}

void Board::operator=(const Board &board1) {}

void Board::resize(int nRow, int nCol) {
  this->nCol = nCol;
  this->nRow = nRow;
}

void Board::load(const std::string &file) {
  std::ifstream mapFile(file);

  if (!mapFile) {
    std::cout << "Unable to open file map.txt" << std::endl;
    exit(EXIT_FAILURE); // call system to stop
  }

  std::vector<int> dataMap;
  while (mapFile) {
    std::string s;
    if (!getline(mapFile, s, ','))
      break;
    dataMap.push_back(std::stoi(s));
  }
  mapFile.close();

  this->nRow = dataMap[0];
  this->nCol = dataMap[1];

  /* tileCode : ABCD

   - A => accessiblity:
            - 0 = inaccessible
            - 1 = accessible

   - B => player:
            - 0 (player id) = neutral
            - 1 (player id) = player 1
            - ...
            - 6 (player id) = player 6

   - C => Entity:
            - 0 = VOID
            - 1 = CASTLE
            - 2 = CAPITAL
            - 3 = PINE
            - 4 = PALM
            - 5 = GRAVESTONE
            - 6 = BARON
            - 7 = KNIGHT
            - 8 = SPEARMAN
            - 9 = PEASANT
  */

  for (int i = 2; i < nRow * nCol + 2; i++) {

    // Inaccessible Cell : 000
    if (dataMap[i] == 000) {
      std::unique_ptr<state::InaccessibleCell> iCellPtr(
          new InaccessibleCell((i - 2) / nCol, (i - 2) % nCol));
      cells.push_back(std::move(iCellPtr));
    }
    // Accessible Cell : 1XX
    else if (dataMap[i] < 200) {
      std::unique_ptr<state::AccessibleCell> aCellPtr(
          new AccessibleCell((i - 2) / nCol, (i - 2) % nCol));

      int players[] = {100, 110, 120, 130, 140, 150, 160};
      bool errorPlayer = true;
      for (int p = 0; p < NB_PLAYER_MAX + 1; p++) {
        if (dataMap[i] >= players[p] && dataMap[i] < players[p] + 10) {
          aCellPtr->setPlayerId(p);
          errorPlayer = false;
        }
      }
      if (errorPlayer) {
        std::cout << "Error map.txt: player nb" << std::endl;
        exit(EXIT_FAILURE);
      }

      bool errorEntity = true;
      for (int e = 0; e < NB_PLAYER_MAX + 1; e++) {
        // Empty Cell
        if (dataMap[i] == players[e]) {
          state::Empty entity(EMPTY, VOID);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Castle Cell
        else if (dataMap[i] == players[e] + 1) {
          state::Facility entity(FACILITY, CASTLE);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Capital Cell
        else if (dataMap[i] == players[e] + 2) {
          state::Facility entity(FACILITY, CAPITAL);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Pine Cell
        else if (dataMap[i] == players[e] + 3) {
          state::Tree entity(TREE, PINE);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Palm Cell
        else if (dataMap[i] == players[e] + 4) {
          state::Tree entity(TREE, PALM);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Gravestone Cell
        else if (dataMap[i] == players[e] + 5) {
          state::Facility entity(FACILITY, GRAVESTONE);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Baron Cell
        else if (dataMap[i] == players[e] + 6) {
          state::Soldier entity(SOLDIER, BARON, 4, 4);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Knight Cell
        else if (dataMap[i] == players[e] + 7) {
          state::Soldier entity(SOLDIER, KNIGHT, 3, 3);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Spearman Cell
        else if (dataMap[i] == players[e] + 8) {
          state::Soldier entity(SOLDIER, SPEARMAN, 2, 2);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
        // Peasant Cell
        else if (dataMap[i] == players[e] + 9) {
          state::Soldier entity(SOLDIER, PEASANT, 1, 1);
          aCellPtr->setEntity(entity);
          errorEntity = false;
        }
      }
      if (errorEntity) {
        std::cout << "Error map.txt: entity" << std::endl;
        exit(EXIT_FAILURE);
      }

      if (dataMap[i] >= players[1]) {
        aCellPtr->getEntity().setIncome(2);
      } else {
        aCellPtr->getEntity().setIncome(0);
      }

      cells.push_back(std::move(aCellPtr));
      // printf("isacc1: %d", cells[i]->isAccessible());
    } else {
      std::cout << "Error map.txt: accessibility" << std::endl;
    }
  }
}

Cell *const Board::get(int r, int c) {}

void Board::set(int r, int c, Cell *cell) {}

void Board::remove(int r, int c) {}

int Board::getNCol() { return nCol; }

int Board::getNRow() { return nRow; }

std::vector<std::unique_ptr<Cell>> &Board::getCells() { return this->cells; }

Board *const Board::clone() {}

bool const Board::equals(const Board &board1) {}
