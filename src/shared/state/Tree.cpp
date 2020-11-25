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

Tree::Tree (const Tree& tree1){}

Tree::~Tree() {}

void Tree::setSubTypeId(TreeTypeId typeId) { this->subTypeId = typeId; }

bool const Tree::operator==(const Entity& e) {}
