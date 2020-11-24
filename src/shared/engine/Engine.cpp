#include "Engine.h"
#include "engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;

Engine::Engine() {}

Engine::~Engine() {}

void Engine::setCurrentState(state::State currentState) {
  this->currentState = currentState;
}

state::State &Engine::getCurrentState() { return this->currentState; }

Json::Value Engine::getRecord() { return this->record; }
