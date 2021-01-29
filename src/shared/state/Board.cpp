#include <fstream>
#include <iostream>
#include <sstream> // stringstream

#include "AccessibleCell.h"
#include "Board.h"
#include "InaccessibleCell.h"

using namespace state;

// -----------------------------------------------------------------------------

#define MAP_TXT_SEP ','

//   NW N NE
//   W  .  E
//   SW S SE
static const int DIRECTIONS[6][2] = {
    {-1, +1}, // NE
    {-1, 0},  // N
    {-1, -1}, // NW
    {0, -1},  // SW
    {1, 0},   // S
    {0, 1}    // SE
};

// -----------------------------------------------------------------------------

Board::Board() {}

Board::Board(const Board &board1) : nRow(board1.nRow), nCol(board1.nCol) {}

Board::Board(int nRow, int nCol) {
  this->nRow = nRow;
  this->nCol = nCol;
}

Board::~Board() {}

void Board::operator=(const Board &board1) {}

/**
 * @brief resize the internal cells vector
 *
 * @param nRow
 * @param nCol
 */
void Board::resize(int nRow, int nCol) {
  this->nRow = nRow;
  this->nCol = nCol;
  // set up cells vector
  cells.clear();
  cells.resize(nCol * nRow);
}

/**
 * @brief return the Cell encoded by the given token
 *
 * /* tileCode : ABC
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

/**
 * @brief load a map into the board
 *
 * @param filename
 */
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
  int r = 0, c = 0;
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
      cells[sub2ind(r, c)] = std::move(cell_ptr);
    }
    // std::cout << std::endl;
  }

  ifs.close();
}

/**
 * @brief return the cells at the location (r, c)
 *
 * @param r
 * @param c
 * @return std::shared_ptr<Cell>
 */
std::shared_ptr<Cell> Board::get(int r, int c) {
  int index = sub2ind(r, c);
  return cells[index];
}

/**
 * @brief return the cells at the given linear index
 *
 * @param index
 * @return std::shared_ptr<Cell>
 */
std::shared_ptr<Cell> Board::get(int index) { return cells[index]; }

void Board::remove(int r, int c) {}

/**
 * @brief return the number of the board's column
 *
 * @return int
 */
int Board::getNCol() { return nCol; }

/**
 * @brief return the number of the board's row
 *
 * @return int
 */
int Board::getNRow() { return nRow; }

/**
 * @brief return the size of the board : nRow * nCol
 *
 * @return int
 */
int Board::getSize() { return nRow * nCol; }

/**
 * @brief linearize sub=(r, c) to ind
 *
 * @param r
 * @param c
 * @return int
 */
int Board::sub2ind(int r, int c) { return r * nCol + c; }

/**
 * @brief de-linearize ind to (r, c)
 *
 * @param ind
 * @return std::pair<int, int>
 */
std::pair<int, int> Board::ind2sub(int ind) {
  int r = ind / nCol;
  int c = ind % nCol;
  return std::make_pair(r, c);
}

/**
 * @brief return the internal cells vector
 *
 * @return std::vector<std::shared_ptr<Cell>>&
 */
std::vector<std::shared_ptr<Cell>> &Board::getCells() { return this->cells; }

bool const Board::operator==(const Board &board1) {}

/**
 * @brief return up to 6 neighbors of the cell at (r, c).
 *
 * @param r0
 * @param c0
 * @return std::vector<std::shared_ptr<Cell>>
 */
std::vector<std::shared_ptr<Cell>> Board::getNeighbors(int r0, int c0) {
  std::vector<std::shared_ptr<state::Cell>> neighbors;
  int r1, c1;
  for (int d = 0; d < 6; ++d) {
    r1 = r0 + DIRECTIONS[d][0];
    c1 = c0 + DIRECTIONS[d][1];
    if (r1 >= 0 && r1 < nRow && c1 >= 0 & c1 < nCol) {
      neighbors.push_back(this->get(r1, c1));
    }
  }
  return neighbors;
}