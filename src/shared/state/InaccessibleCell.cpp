#include "InaccessibleCell.h"

using namespace state;

bool const InaccessibleCell::isAccessible() { return false; }

bool const InaccessibleCell::equals(const Cell &cell1) {}

Cell *const InaccessibleCell::clone() {}
