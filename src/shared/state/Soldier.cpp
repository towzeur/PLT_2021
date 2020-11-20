#include "Soldier.h"

using namespace state;

Soldier::Soldier() {}

Soldier::~Soldier() {}

EntityTypeId const Soldier::getTypeId() {}

bool const Soldier::equals(const Entity &e) {}

Entity *const Soldier::clone() {}

int Soldier::getPA() {return PA;}

void Soldier::setPA(int PA) {this->PA = PA;}
