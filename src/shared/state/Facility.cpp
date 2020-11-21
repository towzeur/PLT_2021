#include "Facility.h"

using namespace state;

Facility::Facility() {}

Facility::~Facility() {}

int Facility::getSubTypeId() { return this->subTypeId; }

void Facility::setSubTypeId(FacilityTypeId typeId) { this->subTypeId = typeId; }

bool const Facility::equals(const Entity &e) {}

Entity *const Facility::clone() {}
