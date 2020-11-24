#include "Command.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

CommandTypeId Command::getCommandTypeId() const { return this->commandTypeId; }