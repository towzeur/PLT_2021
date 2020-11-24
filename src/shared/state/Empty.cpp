#include "Empty.h"
#include <iostream>

using namespace state;

Empty::Empty() {}

Empty::Empty(EntityTypeId entityTypeId, int subTypeId, int attack, int defense,
             int income)
    : Entity() {
  this->entityTypeId = entityTypeId;
  this->subTypeId = subTypeId;
  this->attack = attack;
  this->defense = defense;
  this->income = income;
}

Empty::~Empty() {}

void Empty::setSubTypeId(EmptyTypeId typeId) { this->subTypeId = typeId; }

bool const Empty::equals(const Entity &e) {}

Entity *const Empty::clone() {}
