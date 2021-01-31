#include <iostream>
#include <unistd.h>

#include "ActionBuy.h"
//#include "engine.h"

using namespace engine;

ActionBuy::ActionBuy() {}

Json::Value ActionBuy::serialize() {}

void ActionBuy::deserialize(Json::Value &ser) {}

bool ActionBuy::isLegal(state::State &s) {}

Json::Value ActionBuy::execute(state::State &state) {}

void ActionBuy::print() {}
