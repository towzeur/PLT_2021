
#include "Board.h"
#include "AccessibleCell.h"
#include "InaccessibleCell.h"

#include "Empty.h"
#include "Facility.h"
#include "Soldier.h"
#include "Tree.h"

#include <fstream>
#include <iostream>
#include <sstream> // stringstream

using namespace state;

// -----------------------------------------------------------------------------

#define NB_PLAYER_MAX 6
#define MAP_TEXT_OFFSET 2
#define NEXT_PLAYER_TILECODE_OFFSET 10
#define MAP_TXT_SEP ','

const int ENTITY_ATTACK[5] = {0, 1, 2, 3, 4};
const int ENTITY_DEFENSE[5] = {0, 1, 2, 3, 4};

enum TOKENS {
  TOKEN_VOID = 0,
  TOKEN_FACILITY_CASTLE = 1,
  TOKEN_FACILITY_CAPITAL = 2,
  TOKEN_TREE_PINE = 3,
  TOKEN_TREE_PALM = 4,
  TOKEN_SOLIDER_GRAVESTONE = 5,
  TOKEN_SOLIDER_BARON = 6,
  TOKEN_SOLIDER_KNIGHT = 7,
  TOKEN_SOLIDER_SPEARMAN = 8,
  TOKEN_SOLIDER_PEASANT = 9
};

// -----------------------------------------------------------------------------

Board::Board() {}

Board::Board(int nRow, int nCol) {
  this->nRow = nRow;
  this->nCol = nCol;
}

Board::Board(const Board &board1) {}

Board::~Board() {}

void Board::operator=(const Board &board1) {}

void Board::resize(int nRow, int nCol) {
  this->nCol = nCol;
  this->nRow = nRow;
  // set up cells vector
  cells.clear();
  // cells.resize(nCol * nRow);
}

/**
 * @brief
 *
 * /* tileCode : ABCD
 *
 *  - A => accessiblity:
 *          - 0 = inaccessible
 *          - 1 = accessible
 *
 * - B => player:
 *          - 0 (player id) = neutral
 *          - 1 (player id) = player 1
 *          - ...
 *          - 6 (player id) = player 6
 *
 * - C => Entity:
 *          - 0 = VOID
 *          - 1 = CASTLE
 *          - 2 = CAPITAL
 *          - 3 = PINE
 *          - 4 = PALM
 *          - 5 = GRAVESTONE
 *          - 6 = BARON
 *          - 7 = KNIGHT
 *          - 8 = SPEARMAN
 *          - 9 = PEASANT
 *
 * @param token
 */
std::shared_ptr<Cell> detokenize(std::string token) {
  int a = std::stoi(token.substr(0, 1));
  int b = std::stoi(token.substr(1, 1));
  int c = std::stoi(token.substr(2, 1));

  // if the cell is inacessible
  if (a == 0) {
    std::cout << "... ";
    return std::shared_ptr<Cell>(new InaccessibleCell());
    // return std::make_unique((Cell)InaccessibleCell()) // C++14
  }

  // cell is accessible
  std::cout << a << b << c << " ";
  AccessibleCell *acell = new AccessibleCell();
  acell->setPlayerId(b);

  // parse c : entity
  Entity entity;
  switch (c) {
  case TOKEN_VOID:
    entity = (Entity)Empty(EMPTY, VOID);
    break;
  case TOKEN_FACILITY_CASTLE:
    entity = (Entity)Facility(FACILITY, CASTLE);
    break;
  case TOKEN_FACILITY_CAPITAL:
    entity = (Entity)Facility(FACILITY, CAPITAL);
    break;
  case TOKEN_TREE_PINE:
    entity = (Entity)Tree(TREE, PINE);
    break;
  case TOKEN_TREE_PALM:
    entity = (Entity)Tree(TREE, PALM);
    break;
  case TOKEN_SOLIDER_GRAVESTONE:
    entity = (Entity)Facility(FACILITY, GRAVESTONE);
    break;
  case TOKEN_SOLIDER_BARON:
    entity =
        (Entity)Soldier(SOLDIER, BARON, ENTITY_ATTACK[4], ENTITY_DEFENSE[4]);
    break;
  case TOKEN_SOLIDER_KNIGHT:
    entity =
        (Entity)Soldier(SOLDIER, KNIGHT, ENTITY_ATTACK[3], ENTITY_DEFENSE[3]);
    break;
  case TOKEN_SOLIDER_SPEARMAN:
    entity =
        (Entity)Soldier(SOLDIER, SPEARMAN, ENTITY_ATTACK[2], ENTITY_DEFENSE[2]);
    break;
  case TOKEN_SOLIDER_PEASANT:
    entity =
        (Entity)Soldier(SOLDIER, PEASANT, ENTITY_ATTACK[1], ENTITY_DEFENSE[0]);
    break;
  default:
    std::cout << "default\n";
    break;
  }
  acell->setEntity(entity);

  return std::shared_ptr<Cell>(acell);
}

void tokenize(std::string token) {}

void Board::load(const std::string &filename) {

  // Create the map input file stream
  std::ifstream ifs(filename);
  int n_row = 0, n_col = 0;
  std::string line, tmp_str;

  // check if the file is correctly open
  if (!ifs.is_open()) {
    throw std::runtime_error("Unable to open filename map.txt");
  }

  // read the first line : n_row, n_col
  if (ifs.good()) {                  // check if no error flag are set
    std::getline(ifs, line);         // extract the first line
    std::stringstream sstream(line); // create a stringstream from line
    // read row
    std::getline(sstream, tmp_str, MAP_TXT_SEP);
    n_row = std::stoi(tmp_str);
    // read n_col
    std::getline(sstream, tmp_str, MAP_TXT_SEP);
    n_col = std::stoi(tmp_str);
  }
  resize(n_row, n_col);
  std::cout << n_row << " " << n_col << std::endl;

  // read each line
  int r = 0, c = 0, index;
  std::shared_ptr<state::Cell> cell_ptr;

  for (r = 0; r < n_row; ++r) {
    // get line
    std::getline(ifs, line);
    std::stringstream sstream(line);
    // loop through str token
    for (c = 0; c < n_col; ++c) {
      std::getline(sstream, tmp_str, MAP_TXT_SEP);
      index = c + n_col * r;
      cell_ptr = detokenize(tmp_str);
      cell_ptr->setCol(c);
      cell_ptr->setRow(r);
      cells.push_back(std::move(cell_ptr));
    }
    std::cout << std::endl;
  }

  ifs.close();
}

Cell *const Board::get(int r, int c) {}

void Board::set(int r, int c, Cell *cell) {}

void Board::remove(int r, int c) {}

int Board::getNCol() { return nCol; }

int Board::getNRow() { return nRow; }

std::vector<std::shared_ptr<Cell>> &Board::getCells() { return this->cells; }

Board *const Board::clone() {}

bool const Board::equals(const Board &board1) {}
