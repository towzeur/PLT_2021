#include "Entity.h"
#include <stdexcept>

using namespace state;

int Entity::instanceCount = 0;
Entity::Entity() { this->uid = instanceCount++; }

Entity::~Entity() {}

void Entity::init(EntitySubTypeId subTypeId) {

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
    this->defense = SoldiersStrength::SPEARMAN_STRENGTH;
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
    this->attack = SoldiersStrength::PEASANT_STRENGTH;
    this->defense = SoldiersStrength::PEASANT_STRENGTH;
    this->income = 1 - SoldiersWage::PEASANT_WAGE;
    this->actionPoint = 1;
    break;
  }
  case SOLDIER_SPEARMAN: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_SPEARMAN;
    this->attack = SoldiersStrength::SPEARMAN_STRENGTH;
    this->defense = SoldiersStrength::SPEARMAN_STRENGTH;
    this->income = 1 - SoldiersWage::SPEARMAN_WAGE;
    this->actionPoint = 1;
    break;
  }
  case SOLDIER_KNIGHT: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_KNIGHT;
    this->attack = SoldiersStrength::KNIGHT_STRENGTH;
    this->defense = SoldiersStrength::KNIGHT_STRENGTH;
    this->income = 1 - SoldiersWage::KNIGHT_WAGE;
    this->actionPoint = 1;
    break;
  }
  case SOLDIER_BARON: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_BARON;
    this->attack = SoldiersStrength::BARON_STRENGTH;
    this->defense = SoldiersStrength::BARON_STRENGTH;
    this->income = 1 - SoldiersWage::BARON_WAGE;
    this->actionPoint = 1;
    break;
  }
  default:
    throw std::runtime_error("Unkown entity enum value");
    break;
  }
}

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
  if (!this->isSoldier())
    return 0;
  switch (entitySubTypeId) {
  case EntitySubTypeId::SOLDIER_PEASANT:
    return SoldiersStrength::PEASANT_STRENGTH;
  case EntitySubTypeId::SOLDIER_SPEARMAN:
    return SoldiersStrength::SPEARMAN_STRENGTH;
  case EntitySubTypeId::SOLDIER_KNIGHT:
    return SoldiersStrength::KNIGHT_STRENGTH;
  case EntitySubTypeId::SOLDIER_BARON:
    return SoldiersStrength::BARON_STRENGTH;
  default:
    throw std::runtime_error("getStrength unknow Soldier");
  }
}

void Entity::setStrength(int newStrength) {
  switch (newStrength) {
  case SoldiersStrength::PEASANT_STRENGTH:
    this->init(SOLDIER_PEASANT);
    break;
  case SoldiersStrength::SPEARMAN_STRENGTH:
    this->init(SOLDIER_SPEARMAN);
    break;
  case SoldiersStrength::KNIGHT_STRENGTH:
    this->init(SOLDIER_KNIGHT);
    break;
  case SoldiersStrength::BARON_STRENGTH:
    this->init(SOLDIER_BARON);
    break;
  default:
    break;
  }
}

bool Entity::isValidStrength(int newStrength) {
  switch (newStrength) {
  case SoldiersStrength::PEASANT_STRENGTH:
    return true;
  case SoldiersStrength::SPEARMAN_STRENGTH:
    return true;
  case SoldiersStrength::KNIGHT_STRENGTH:
    return true;
  case SoldiersStrength::BARON_STRENGTH:
    return true;
  default:
    break;
  }
  return false;
}

int Entity::getWage() {
  if (!this->isSoldier())
    return 0;

  switch (entitySubTypeId) {
  case EntitySubTypeId::SOLDIER_PEASANT:
    return SoldiersWage::PEASANT_WAGE;
  case EntitySubTypeId::SOLDIER_SPEARMAN:
    return SoldiersWage::SPEARMAN_WAGE;
  case EntitySubTypeId::SOLDIER_KNIGHT:
    return SoldiersWage::KNIGHT_WAGE;
  case EntitySubTypeId::SOLDIER_BARON:
    return SoldiersWage::BARON_WAGE;
  default:
    throw std::runtime_error("getWage unknow Soldier");
  }
}