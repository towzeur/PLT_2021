#include "AccessibleCell.h"

using namespace state;

AccessibleCell::AccessibleCell(){};

AccessibleCell::AccessibleCell(int row, int col) : Cell() {
  this->col = col;
  this->row = row;
}

AccessibleCell::AccessibleCell (const AccessibleCell& accessCell1){}

AccessibleCell::~AccessibleCell(){};

int AccessibleCell::getPlayerId() { return this->playerId; }

void AccessibleCell::setPlayerId(int playerId) { this->playerId = playerId; }

int AccessibleCell::getTerritoryId() { return this->territoryId; }

void AccessibleCell::setTerritoryId(int territoryId) {
  this->territoryId = territoryId;
}

Entity &AccessibleCell::getEntity() { return this->entity; }

void AccessibleCell::setEntity(Entity &entity) { this->entity = entity; }

bool const AccessibleCell::operator== (const Cell &cell1) {}

bool const AccessibleCell::isAccessible() { return true; }
