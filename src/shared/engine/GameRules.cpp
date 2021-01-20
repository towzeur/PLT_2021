#include "GameRules.h"

/**
 * @brief check if the move (r0, c0) to (r1, c1) is legal
 *
 * @param r0
 * @param c0
 * @param r1
 * @param c1
 * @return true
 * @return false
 */
bool GameRules::action_soldier_valid(state::Board &b, int r0, int c0, int r1,
                                     int c1) {
  int n_row = b.getNRow(), n_col = b.getNCol();

  // check that the two position are within the map
  if ((r0 < 0 || r0 >= n_row) || (c0 < 0 || c0 >= n_col))
    return false;
  if ((r1 < 0 || r1 >= n_row) || (c1 < 0 || c1 >= n_col))
    return false;

  // same cell
  if (r0 == r1 && c0 == c1)
    return false;

  // retrieve the two cell
  std::shared_ptr<state::Cell> cell0 = b.get(r0, c0);
  std::shared_ptr<state::Cell> cell1 = b.get(r1, c1);

  if (!cell0->isAccessible() || !cell1->isAccessible())
    return false;

  return true;
}

int GameRules::action_soldier(state::Board &b, int r0, int c0, int r1, int c1) {
  if (action_soldier_valid(r0, c0, r1, c1))
    return ActionsTypeId::NOTHING;

  state::AccessibleCell *ac0 = b.get(r0, c0)->castAccessible();
  state::AccessibleCell *ac1 = b.get(r1, c1)->castAccessible();

  state::Entity &e0 = ac0->getEntity();
  state::Entity &e1 = ac1->getEntity();

  if (!e0.isSoldier()) // assert that the first cell is a soldier
    return ActionsTypeId::NOTHING;

  if (ac0->getPlayerId() == ac0->getPlayerId()) { // same player
    // the target cell must be on the same territory
    if (ac0->getTerritoryId() == ac0->getTerritoryId()) {
      if (e1.isEmpty())
        return ActionsTypeId::SOLDIER_MOVE;
      else if (e1.isTree())
        return ActionsTypeId::SOLDIER_ATTACK;
      else if (e1.isFacility())
        return ActionsTypeId::NOTHING;
      else if (e1.isSoldier())
        return ActionsTypeId::SOLDIER_FUSION;
    } else
      return ActionsTypeId::NOTHING;
  } else // different player
    return ActionsTypeId::SOLDIER_ATTACK;

  // throw error
}
