#include "Empty.h"

using namespace state;

Empty::Empty() {}

Empty::~Empty() {}

int Empty::getSubTypeId() { return this->subTypeId; }

void Empty::setSubTypeId(EmptyTypeId typeId) { this->subTypeId = typeId; }

bool const Empty::equals(const Entity &e) {}

Entity *const Empty::clone() {}
