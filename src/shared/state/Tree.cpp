#include "Tree.h"

using namespace state;

Tree::Tree() {}

Tree::~Tree() {}

int Tree::getSubTypeId() { return this->subEntityTypeId; }

bool const Tree::equals(const Entity &e) {}

Entity *const Tree::clone() {}
