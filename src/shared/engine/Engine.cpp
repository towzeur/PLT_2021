#include "Engine.h"
#include <iostream>

using namespace state;
using namespace engine;

Engine::~Engine(){}
state::State& getState (){}
void Engine::addPassiveCommands (){}
void Engine::addCommand (std::unique_ptr<Command> ptr_cmd, int priority = -1){}
void Engine::update (){}
void Engine::setState (state::State& newState){}
Engine::Engine (std::string stateMode){}
Json::Value getRecord (){}
std::map<int, std::unique_ptr<Command>>& getCurrentCommands (){}

bool Engine::getEnableRecord(){return enableRecord;}
void Engine::setEnableRecord(bool enableRecord){}
void Engine::setRecord(const Json::Value& record){}
bool Engine::getStop(){return stop;}
void Engine::setStop(bool stop){this->stop = stop;}