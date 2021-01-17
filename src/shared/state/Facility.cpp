#include "Facility.h"

using namespace state;

Facility::Facility() {}

Facility::Facility(EntityTypeId entityTypeId, int subTypeId, int attack,
                   int defense, int income)
    : Entity() {
  this->entityTypeId = entityTypeId;
  this->subTypeId = subTypeId;
  this->attack = attack;
  this->defense = defense;
  this->income = income;
}

Facility::~Facility() {}

Facility::Facility (const Facility& facility1){}

void Facility::setSubTypeId(FacilityTypeId typeId) { this->subTypeId = typeId; }

bool const Facility::operator== (const Entity& e) {}