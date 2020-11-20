#include "Entity.h"

using namespace state;

bool const Entity::isEmpty() {}

bool const Entity::isTree() {}

bool const Entity::isFacility() {}

bool const Entity::isSoldier() {}

int Entity::getUid() {}

int Entity::getAttack() const {}

void Entity::setAttack(int attack) {}

int Entity::getDefense() const {}

void Entity::setDefense(int defense) {}

int Entity::getIncome() const {}

void Entity::setIncome(int income) {}

int Entity::getSubTypeId() {}

EntityTypeId const Entity::getEntityTypeId() { return this->entityTypeId; }

bool const Entity::equals(const Entity &e) {}

Entity *const Entity::clone() {}
