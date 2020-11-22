#include "AccessibleCell.h"

using namespace state;

AccessibleCell::AccessibleCell(){};

AccessibleCell::AccessibleCell(int row, int col) : Cell() {
  this->col = col;
  this->row = row;
}

AccessibleCell::~AccessibleCell(){};

int AccessibleCell::getPlayerId() { return this->playerId; }

void AccessibleCell::setPlayerId(int playerId) { this->playerId = playerId; }

int AccessibleCell::getTerritoryId() { return this->territoryId; }

void AccessibleCell::setTerritoryId(int territoryId) {
  this->territoryId = territoryId;
}

Entity AccessibleCell::getEntity() { return this->entity; }

void AccessibleCell::setEntity(Entity entity) { this->entity = entity; }

bool const AccessibleCell::equals(const Cell &cell1) {}

Cell *const AccessibleCell::clone() {}

bool const AccessibleCell::isAccessible() { return true; }
