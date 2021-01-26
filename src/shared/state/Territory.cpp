#include "Territory.h"

using namespace state;

int Territory::instanceCount = 0;
Territory::Territory() : savings(0) { this->uid = instanceCount++; }

Territory::Territory(const Territory &territory1) {}

Territory::~Territory() {}

int Territory::getUid() { return uid; }

/**
 * @brief return the territory's savings
 *
 * @return int
 */
int Territory::computeSavings() { return this->savings; }

/**
 * @brief compute the total sum of Every Entity's income
 *        Income = nb_cells - nb_trees
 *
 * @return int
 */
int Territory::computeIncome() {
  int income = 0;
  state::AccessibleCell *ac;
  for (auto &cell_ptr : cells) {
    ac = cell_ptr->castAccessible();
    income += ac->getEntity().getIncome();
  }
  return income;
}

/**
 * @brief compute the total sum of Soldier's wages
 *
 * @return int
 */
int Territory::computeWages() {
  int wages = 0;
  state::AccessibleCell *ac;
  for (auto &cell_ptr : cells) {
    ac = cell_ptr->castAccessible();
    // getWage return 0 when not a soldier
    wages += ac->getEntity().getWage();
  }
  return wages;
}

/**
 * @brief compute the actual balance of the territory :
 *        balance = savings + income - wages
 *
 * @return int
 */
int Territory::computeBalance() {
  return computeSavings() + computeIncome() - computeWages();
}

void Territory::addCell(std::shared_ptr<Cell> cell) { cells.push_back(cell); }

std::vector<std::shared_ptr<Cell>> Territory::getCells() { return cells; }
