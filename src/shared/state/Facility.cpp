#include "Facility.h"

using namespace state;

Facility::Facility() {}

Facility::~Facility() {}

int Facility::getSubTypeId() { return this->subEntityTypeId; }

bool const Facility::equals(const Entity &e) {}

Entity *const Facility::clone() {}
