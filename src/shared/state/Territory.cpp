#include "Territory.h"

using namespace state;

int Territory::instanceCount = 0;

Territory::Territory() : savings(0) { this->uid = instanceCount++; }

Territory::Territory (const Territory& territory1) {}

Territory::~Territory() {}

int Territory::getUid() { return uid; }

int Territory::getCapitalRow() { return capitalRow; }

void Territory::setCapitalRow(int r) { capitalRow = r; }

int Territory::getCapitalCol() { return capitalCol; }

void Territory::setCapitalCol(int c) { capitalCol = c; }

void Territory::setCapitalCoords(int cRow, int cCol) {
  capitalCol = cCol;
  capitalRow = cRow;
}

int Territory::getSavings() { return savings; }

void Territory::setSavings(int savings) { this->savings = savings; }

int Territory::getIncome() { return income; }

void Territory::setIncome(int income) { this->income = income; }

int Territory::getWages() { return wages; }

void Territory::setWages(int wages) { this->wages = wages; }

int Territory::getBalance() { return balance; }

void Territory::setBalance(int balance) { this->balance = balance; }

int Territory::getSize() { return size; }

void Territory::setSize(int size) { this->size = size; }

void Territory::setSelected(bool selected) { this->selected = selected; }

bool Territory::isSelected() { return this->selected; }

bool const Territory::operator== (const Territory& t1) {}