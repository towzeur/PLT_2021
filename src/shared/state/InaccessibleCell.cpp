#include "InaccessibleCell.h"

using namespace state;

InaccessibleCell::InaccessibleCell(){};

InaccessibleCell::InaccessibleCell(int row, int col) : Cell() {
  this->col = col;
  this->row = row;
}

InaccessibleCell::~InaccessibleCell(){};

InaccessibleCell::InaccessibleCell (const InaccessibleCell& inacCell1){}

bool const InaccessibleCell::isAccessible() { return false; }

bool const InaccessibleCell::operator== (const Cell& cell1) {}