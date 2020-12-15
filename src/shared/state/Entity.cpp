#include "Entity.h"

using namespace state;

int Entity::instanceCount = 0;

Entity::Entity() { this->uid = instanceCount++; }

Entity::~Entity() {}

bool const Entity::isEmpty() {
  if (this->entityTypeId == EMPTY) {
    return true;
  } else {
    return false;
  }
}

bool const Entity::isTree() {
  if (this->entityTypeId == TREE) {
    return true;
  } else {
    return false;
  }
}

bool const Entity::isFacility() {
  if (this->entityTypeId == FACILITY) {
    return true;
  } else {
    return false;
  }
}

bool const Entity::isSoldier() {
  if (this->entityTypeId == SOLDIER) {
    return true;
  } else {
    return false;
  }
}

int Entity::getUid() { return this->uid; }

int Entity::getAttack() const { return this->attack; }

void Entity::setAttack(int attack) { this->attack = attack; }

int Entity::getDefense() const { return this->defense; }

void Entity::setDefense(int defense) { this->defense = defense; }

int Entity::getIncome() const { return this->income; }

void Entity::setIncome(int income) { this->income = income; }

int Entity::getSubTypeId() { return subTypeId; }

void Entity::setEntityTypeId(EntityTypeId entityTypeId) {
  this->entityTypeId = entityTypeId;
}

EntityTypeId const Entity::getEntityTypeId() { return this->entityTypeId; }

void Entity::setPA (int PA){ this->PA = PA;}
int Entity::getPA (){return this->PA; }

bool const Entity::equals(const Entity & element) {}

Entity *const Entity::clone() {}
