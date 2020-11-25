#include "Command.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

CommandTypeId Command::getCommandTypeId() const { return this->commandTypeId; }

void Command::setCommandTypeId(CommandTypeId commandTypeId){ this->commandTypeId = commandTypeId; }

const state::PlayerStatus& Command::getCurrentPlayerStatus() const{ return this->currentPlayerStatus; }

void Command::setCurrentPlayerStatus(const state::PlayerStatus& currentPlayerStatus){ this->currentPlayerStatus=currentPlayerStatus; }

