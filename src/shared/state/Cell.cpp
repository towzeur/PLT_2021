#include "Cell.h"

#include "AccessibleCell.h"

using namespace state;

Cell::Cell() {}

Cell::~Cell() {}

int Cell::getRow() { return this->row; }

void Cell::setRow(int row) { this->row = row; }

int Cell::getCol() { return this->col; }

void Cell::setCol(int col) { this->col = col; }

bool const Cell::isAccessible() {}

state::AccessibleCell *Cell::castAccessible() {
  if (!this->isAccessible())
    return nullptr;
  return (AccessibleCell *)this;
}