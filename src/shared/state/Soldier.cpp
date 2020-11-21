#include "Soldier.h"

using namespace state;

Soldier::Soldier() {}

Soldier::~Soldier() {}

int Soldier::getSubTypeId() { return this->subTypeId; }

void Soldier::setSubTypeId(SoldierTypeId typeId) { this->subTypeId = typeId; }

bool const Soldier::equals(const Entity &e) {}

Entity *const Soldier::clone() {}

int Soldier::getPA() { return this->PA; }

void Soldier::setPA(int PA) { this->PA = PA; }
