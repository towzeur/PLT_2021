#include "BuyEntityCommand.h"
//#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

BuyEntityCommand::BuyEntityCommand(state::Entity &target,
                                   state::Cell &cellTarget)
    : target(target), cellTarget(cellTarget) {
  this->commandTypeId = BUY_SOLDIER;
}

void BuyEntityCommand::execute(state::State &state) {}