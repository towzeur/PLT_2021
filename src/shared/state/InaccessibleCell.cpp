#include "InaccessibleCell.h"

using namespace state;

InaccessibleCell::InaccessibleCell(){};

InaccessibleCell::InaccessibleCell(int row, int col) : Cell() {
  this->col = col;
  this->row = row;
}

InaccessibleCell::~InaccessibleCell(){};

bool const InaccessibleCell::isAccessible() { return false; }

bool const InaccessibleCell::equals(const Cell &cell1) {}

Cell *const InaccessibleCell::clone() {}
