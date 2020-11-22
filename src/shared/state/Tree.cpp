#include "Tree.h"

using namespace state;

Tree::Tree() {}

Tree::Tree(EntityTypeId entityTypeId, int subTypeId, int attack, int defense,
           int income)
    : Entity() {
  this->entityTypeId = entityTypeId;
  this->subTypeId = subTypeId;
  this->attack = attack;
  this->defense = defense;
  this->income = income;
}

Tree::~Tree() {}

void Tree::setSubTypeId(TreeTypeId typeId) { this->subTypeId = typeId; }

bool const Tree::equals(const Entity &e) {}

Entity *const Tree::clone() {}
