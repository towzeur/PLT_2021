#include "Entity.h"
#include <stdexcept>

using namespace state;

int Entity::instanceCount = 0;

Entity::Entity() { this->uid = instanceCount++; }

Entity::Entity(EntitySubTypeId subTypeId) {
  this->uid = instanceCount++;

  this->attack = 0;
  this->defense = 0;
  this->income = 0;
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
    break;
  }
  case TREE_PALM: {
    this->entityTypeId = state::EntityTypeId::TREE;
    this->entitySubTypeId = state::EntitySubTypeId::TREE_PALM;
    break;
  }
  case FACILITY_CAPITAL: {
    this->entityTypeId = state::EntityTypeId::FACILITY;
    this->entitySubTypeId = state::EntitySubTypeId::FACILITY_CAPITAL;
    break;
  }
  case FACILITY_CASTLE: {
    this->entityTypeId = state::EntityTypeId::FACILITY;
    this->entitySubTypeId = state::EntitySubTypeId::FACILITY_CASTLE;
    break;
  }
  case FACILITY_GRAVESTONE: {
    this->entityTypeId = state::EntityTypeId::FACILITY;
    this->entitySubTypeId = state::EntitySubTypeId::FACILITY_GRAVESTONE;
    break;
  }
  case SOLDIER_PEASANT: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_PEASANT;
    break;
  }
  case SOLDIER_SPEARMAN: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_SPEARMAN;
    break;
  }
  case SOLDIER_KNIGHT: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_KNIGHT;
    break;
  }
  case SOLDIER_BARON: {
    this->entityTypeId = state::EntityTypeId::SOLDIER;
    this->entitySubTypeId = state::EntitySubTypeId::SOLDIER_BARON;
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
