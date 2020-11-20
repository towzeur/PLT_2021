#include "AccessibleCell.h"

using namespace state;

int AccessibleCell::getPlayerId() { return this->playerId; }

void AccessibleCell::setPlayerId(int playerId) {}

int AccessibleCell::getTerritoryId() {}

void AccessibleCell::setTerritoryId(int territoryId) {}

Entity AccessibleCell::getEntity() {}

void AccessibleCell::setEntity(Entity entity) {}

bool const AccessibleCell::equals(const Cell &cell1) {}

Cell *const AccessibleCell::clone() {}

bool const AccessibleCell::isAccessible() { return true; }
