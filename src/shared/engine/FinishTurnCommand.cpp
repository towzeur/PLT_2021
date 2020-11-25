#include "FinishTurnCommand.h"
#include <iostream>


using namespace engine;
using namespace state;
using namespace std;


FinishTurnCommand::FinishTurnCommand (){ Command::commandTypeId=FINISH_TURN; }

Json::Value FinishTurnCommand::serialize (){
    Json::Value newCommand;
    return newCommand["commandTypeId"]= commandTypeId;
}

