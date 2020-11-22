#include "Soldier.h"

using namespace state;

Soldier::Soldier() {}

Soldier::Soldier(EntityTypeId entityTypeId, int subTypeId, int attack,
                 int defense, int income)
    : Entity() {
  this->entityTypeId = entityTypeId;
  this->subTypeId = subTypeId;
  this->attack = attack;
  this->defense = defense;
  this->income = income;
}

Soldier::~Soldier() {}

void Soldier::setSubTypeId(SoldierTypeId typeId) { this->subTypeId = typeId; }

bool const Soldier::equals(const Entity &e) {}

Entity *const Soldier::clone() {}

int Soldier::getPA() { return this->PA; }

void Soldier::setPA(int PA) { this->PA = PA; }
