#include "Action.h"

using namespace engine;

Action::Action() {}

Action *Action::getAction(ActionId a_id) {
  switch (a_id) {
  case engine::ActionId::SOLDIER:
    return (Action *)new ActionSoldier();

  case engine::ActionId::SELECT_TERRITORY:
    return (Action *)new ActionSelectTerritory();

  case engine::ActionId::BUY:
    return (Action *)new ActionBuy();

  case engine::ActionId::END_TURN:
    return (Action *)new ActionEndTurn();

  default:
    throw std::runtime_error("Unkown engine::ActionId");
  }
}

Json::Value Action::serialize() {}

void Action::deserialize(Json::Value &ser) {}

void Action::execute(state::State &state) {}

void Action::print() {}