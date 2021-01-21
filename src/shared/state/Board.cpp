#include <fstream>
#include <iostream>
#include <sstream> // stringstream

#include "AccessibleCell.h"
#include "Board.h"
#include "InaccessibleCell.h"

using namespace state;

// -----------------------------------------------------------------------------

//#define NB_PLAYER_MAX 6
//#define MAP_TEXT_OFFSET 2
//#define NEXT_PLAYER_TILECODE_OFFSET 10
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

const TOKENS all[] = {
    TOKEN_VOID,           TOKEN_FACILITY_CASTLE, TOKEN_FACILITY_CAPITAL,
    TOKEN_TREE_PINE,      TOKEN_TREE_PALM,       TOKEN_SOLIDER_GRAVESTONE,
    TOKEN_SOLIDER_BARON,  TOKEN_SOLIDER_KNIGHT,  TOKEN_SOLIDER_SPEARMAN,
    TOKEN_SOLIDER_PEASANT};

// -----------------------------------------------------------------------------

Board::Board() {}

Board::Board(const Board &board1) : nRow(board1.nRow), nCol(board1.nCol) {}

Board::Board(int nRow, int nCol) {
  this->nRow = nRow;
  this->nCol = nCol;
}

Board::~Board() {}

void Board::operator=(const Board &board1) {}

void Board::resize(int nRow, int nCol) {
  this->nRow = nRow;
  this->nCol = nCol;
  // set up cells vector
  cells.clear();
  cells.resize(nCol * nRow);
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
 *          - 1 = PINE
 *          - 2 = PALM
 *          - 3 = CAPITAL
 *          - 4 = CASTLE
 *          - 5 = GRAVESTONE
 *          - 6 = PEASANT
 *          - 7 = SPEARMAN
 *          - 8 = KNIGHT
 *          - 9 = BARON
 *
 * @param token
 */
std::shared_ptr<Cell> Board::detokenize(std::string token) {
  int a = std::stoi(token.substr(0, 1));
  int b = std::stoi(token.substr(1, 1));
  int c = std::stoi(token.substr(2, 1));

  // if the cell is inacessible
  if (a == 0) {
    // std::cout << "... ";
    return std::shared_ptr<Cell>(new InaccessibleCell());
    // return std::make_unique((Cell)InaccessibleCell()) // C++14
  }

  // cell is accessible
  // std::cout << a << b << c << " ";
  AccessibleCell *acell = new AccessibleCell();
  acell->setPlayerId(b);

  // state::Entity entity(static_cast<state::EntitySubTypeId>(c));
  state::EntitySubTypeId sid = (state::EntitySubTypeId)c;
  acell->getEntity().init(sid);
  return std::shared_ptr<Cell>(acell);
}

// void Board::tokenize(std::string token) {}

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
  // std::cout << n_row << " " << n_col << std::endl;

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

      cell_ptr = Board::detokenize(tmp_str);
      cell_ptr->setCol(c);
      cell_ptr->setRow(r);

      // add it to the cells vector
      cells[c + n_col * r] = std::move(cell_ptr);
    }
    // std::cout << std::endl;
  }

  ifs.close();
}

std::shared_ptr<Cell> Board::get(int r, int c) {
  int index = r * nCol + c;
  return cells[index];
}

void Board::set(int r, int c, Cell *cell) {}

void Board::remove(int r, int c) {}

int Board::getNCol() { return nCol; }

int Board::getNRow() { return nRow; }

std::vector<std::shared_ptr<Cell>> &Board::getCells() { return this->cells; }

bool const Board::operator==(const Board &board1) {}
