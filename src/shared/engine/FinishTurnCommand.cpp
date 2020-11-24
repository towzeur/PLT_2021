#include "FinishTurnCommand.h"
#include <iostream>


using namespace engine;
using namespace state;
using namespace std;


FinishTurnCommand::FinishTurnCommand (){ Command::setCommandTypeId(FINISH_TURN); }