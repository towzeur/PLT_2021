#include "Tree.h"

using namespace state;

Tree::Tree() {}

Tree::~Tree() {}

int Tree::getSubTypeId() { return this->subTypeId; }

void Tree::setSubTypeId(TreeTypeId typeId) { this->subTypeId = typeId; }

bool const Tree::equals(const Entity &e) {}

Entity *const Tree::clone() {}
