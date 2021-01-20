#include "Entity.h"
#include <stdexcept>

using namespace state;

#define SOLDIER_PEASANT_WAGE 2
#define SOLDIER_SPEARMAN_WAGE 6
#define SOLDIER_KNIGHT_WAGE 18
#define SOLDIER_BARON_WAGE 54

#define SOLDIER_PEASANT_STRENGTH 1
#define SOLDIER_SPEARMAN_STRENGTH 2
#define SOLDIER_KNIGHT_STRENGTH 3
#define SOLDIER_BARON_STRENGTH 4

int Entity::instanceCount = 0;

Entity::Entity() { this->uid = instanceCount++; }

Entity::Entity(EntitySubTypeId subTypeId) {
  this->uid = instanceCount++;

  this->attack = 0;
  this->defense = 0;
  this->income = 1;
  this->actionPoint = 0;

  switch (subTypeId) {
  case EMPTY_VOID: {
    this->entityTypeId = state::EntityTypeId::EMPTY;
    this->entitySubTypeId = state::EntitySubTypeId::EMPTY_VOID;
    break;
  }
  case TREE_PINE: {
    this->entityTypeId = state::EntityTypeId::TREE;
    this->entitySubTypeId = state::EntitySubTypeId::TREE_PINE;
    this->income = -1;
    break;
  }
  case TREE_PALM: {
    this->entityTypeId = state::EntityTypeId::TREE;
    this->entitySubTypeId = state::EntitySubTypeId::TREE_PALM;
    this->income = -1;
    break;
  }
  case FACILITY_CAPITAL: {
    this->entityTypeId = state::EntityTypeId::FACILITY;
    this->entitySubTypeId = state::EntitySubTypeId::FACILITY_CAPITAL;
    this->defense = 1;
    break;
  }
  case FACILITY_CASTLE: {
    this->entityTypeId = state::EntityTypeId::FACILITY;
    this->entitySubTypeId = state::EntitySubTypeId::FACILITY_CASTLE;
    this->defense = SOLDIER_SPEARMAN_STRENGTH;
    break;
  }
  case FACILITY_GRAVESTONE: {
    this->entityTypeId = state::EntityTypeId::FACILITY;
    this->entitySubTypeId = state::EntitySubTypeId::FACILITY_GRAVESTONE;
    this->income = 0;
    break;
  }
    // -------------------------------------------------------------------------
    // SOLDIER
    // -------------------------------------------------------------------------
  case SOLDIER_PEASANT: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_PEASANT;
    this->attack = SOLDIER_PEASANT_STRENGTH;
    this->defense = SOLDIER_PEASANT_STRENGTH;
    this->income = 1 - SOLDIER_PEASANT_WAGE;
    this->actionPoint = 1;
    break;
  }
  case SOLDIER_SPEARMAN: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_SPEARMAN;
    this->attack = SOLDIER_SPEARMAN_STRENGTH;
    this->defense = SOLDIER_SPEARMAN_STRENGTH;
    this->income = SOLDIER_SPEARMAN_WAGE + 1;
    this->actionPoint = 1;
    break;
  }
  case SOLDIER_KNIGHT: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_KNIGHT;
    this->attack = SOLDIER_KNIGHT_STRENGTH;
    this->defense = SOLDIER_KNIGHT_STRENGTH;
    this->income = SOLDIER_KNIGHT_WAGE + 1;
    this->actionPoint = 1;
    break;
  }
  case SOLDIER_BARON: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_BARON;
    this->attack = SOLDIER_BARON_STRENGTH;
    this->defense = SOLDIER_BARON_STRENGTH;
    this->actionPoint = 1;
    break;
  }
  default:
    throw std::runtime_error("Unkown entity enum value");
    break;
  }
}

Entity::~Entity() {}

int Entity::getUid() { return this->uid; }

bool Entity::isEmpty() {
  return this->entityTypeId == state::EntityTypeId::EMPTY;
}

bool Entity::isTree() {
  return this->entityTypeId == state::EntityTypeId::TREE;
}

bool Entity::isFacility() {
  return this->entityTypeId == state::EntityTypeId::FACILITY;
}

bool Entity::isSoldier() {
  return this->entityTypeId == state::EntityTypeId::SOLDIER;
}

EntityTypeId Entity::getEntityTypeId() { return this->entityTypeId; }

EntitySubTypeId Entity::getEntitySubTypeId() { return this->entitySubTypeId; }

void Entity::setActionPoint(int ap) { this->actionPoint = ap; }

int Entity::getActionPoint() { return this->actionPoint; }

void Entity::reset() {
  if (this->isSoldier())
    this->actionPoint = 1;
}

int Entity::getStrength() {
  if (this->isSoldier()) {
    switch (entitySubTypeId) {
    case EntitySubTypeId::SOLDIER_PEASANT:
      return SOLDIER_PEASANT_STRENGTH;
    case EntitySubTypeId::SOLDIER_SPEARMAN:
      return SOLDIER_SPEARMAN_STRENGTH;
    case EntitySubTypeId::SOLDIER_KNIGHT:
      return SOLDIER_KNIGHT_STRENGTH;
    case EntitySubTypeId::SOLDIER_BARON:
      return SOLDIER_BARON_STRENGTH;
    default:
      throw std::runtime_error("getStrength unknow Soldier");
    }
  }
  return 0;
}