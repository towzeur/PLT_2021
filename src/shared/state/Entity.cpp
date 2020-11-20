#include "Entity.h"

using namespace state;

bool const Entity::isEmpty() {}

bool const Entity::isTree() {}

bool const Entity::isFacility() {}

bool const Entity::isSoldier() {}

int Entity::getUid() {}

int Entity::getAttack() const {return attack;}

void Entity::setAttack(int attack) {this->attack = attack;}

int Entity::getDefense() const {return defense;}

void Entity::setDefense(int defense) {this->defense = defense;}

int Entity::getIncome() const {return income;}

void Entity::setIncome(int income) {this->income = income;}

int Entity::getSubTypeId() {}

EntityTypeId const Entity::getEntityTypeId() { return this->entityTypeId; }

bool const Entity::equals(const Entity &e) {}

Entity *const Entity::clone() {}
