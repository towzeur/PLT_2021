#include "Cell.h"

using namespace state;

Cell::Cell() {}

Cell::~Cell() {}

bool const Cell::equals(const Cell &cell1) {}

Cell *const Cell::clone() {}

int Cell::getRow() { return this->row; }

void Cell::setRow(int row) { this->row = row; }

int Cell::getCol() { return this->col; }

void Cell::setCol(int col) { this->col = col; }

bool const Cell::isAccessible() {}

int Cell::getPlayerId() {}

Entity &Cell::getEntity() {}

void Cell::setEntity(Entity &entity) {}

void Cell::setTerritoryId(int territoryId) {}

int Cell::getTerritoryId() {}

void Cell::setPlayerId(int playerId) {}
