#include "Board.h"

using namespace state;

Board::Board() : nCol(50), nRow(50) {}

Board::Board(const Board &board1) {}

Board::~Board() {}

void Board::operator=(const Board &board1) {}

void Board::resize(int nRow, int nCol) {
  this->nCol = nCol;
  this->nRow = nRow;
}

void Board::load(const std::string &file) {}

Cell *const Board::get(int r, int c) {}

void Board::set(int r, int c, Cell *cell) {}

void Board::remove(int r, int c) {}

int Board::getNCol() { return nCol; }

int Board::getNRow() { return nRow; }

std::vector<Cell> Board::getCells() {}

Board *const Board::clone() {}

bool const Board::equals(const Board &board1) {}
