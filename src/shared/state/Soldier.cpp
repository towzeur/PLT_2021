#include "Soldier.h"

using namespace state;

Soldier::Soldier() {}

Soldier::~Soldier() {}

int Soldier::getSubTypeId() { return this->subEntityTypeId; }

bool const Soldier::equals(const Entity &e) {}

Entity *const Soldier::clone() {}

int Soldier::getPA() {return PA;}

void Soldier::setPA(int PA) {this->PA = PA;}
